#!/usr/bin/env python3

# missing from RegisterAllPPClasses():
#  69636e70 LIconPane
#  67626f78 LGroupBox
#  74786274 LTextButton

import concurrent.futures
import json
import os
import subprocess
import time

args = ['mpw-emu', 'tools/MWCPPC_20']
libs = [
	':libs:Libraries:Runtime:Runtime PPC:MSL RuntimePPC++.DLL',
	':libs:Libraries:MacOS Common:InterfaceLib',
	':libs:Libraries:MacOS Common:StdCLib',
	':libs:Libraries:Runtime:Runtime PPC:MSL ShLibRuntime.Lib'
]
pp_dirs = [
    '_In Progress/_Appearance Classes/Appearance Controls',
    '_In Progress/_Appearance Classes/Appearance Support',
    '_In Progress/_Appearance Classes/GA Implementations',
    '_In Progress/_Appearance Classes/Std Implementations',
    '_In Progress/_Constructor Additions/Array classes',
    '_In Progress/_Constructor Additions/Feature classes',
    '_In Progress/_Constructor Additions/Outline table',
    '_In Progress/_Constructor Additions/Pane classes',
    '_In Progress/_Constructor Additions/Table classes',
    '_In Progress/_Constructor Additions/Text editing',
    '_In Progress/_Constructor Additions/Utility classes',
    '_In Progress/_Graphics Utility Classes',
    '_In Progress/_Grayscale Classes',
    '_In Progress/New Panes',
    '_Will be Obsolete',
    '_Will be Obsolete/Old GA Classes/General Utility Classes',
    '_Will be Obsolete/Old GA Classes/Grayscale Box Classes',
    '_Will be Obsolete/Old GA Classes/Grayscale Command Controls',
    '_Will be Obsolete/Old GA Classes/Grayscale Controls',
    '_Will be Obsolete/Old GA Classes/Grayscale Pane Classes',
    '_Will be Obsolete/Old GA Classes/Grayscale Utilities Classes',
    'Action Classes',
    'AppleEvent Classes',
    'Array Classes',
    'Commander Classes',
    'Feature Classes',
    'File & Stream Classes',
    'Pane Classes',
    'Support Classes',
    'Table Classes',
    'Utility Classes',
]
excluded = set([
    'LClipboard.cp',
    'LDragAndDrop.cp',
    'LDragTask.cp',
    'LMercutioMBAR.cp',
    'LMouseTracker.cp',
    'LPreferencesFile.cp',
    'LSharable.cp',
    'LSharableModel.cp',
    'LSharablePtr.cp',
    'LSimpleAEAction.cp',
    'LSIOUXAttachment.cp',
    'LTableMonoGeometry.cp',
    'LTableSingleSelector.cp',
    'LTextEditView.cp',
    'UControlRegistry.cp',
    'UDesktop.cp', # they use UFloatingDesktop.cp instead
    'UException.cp', # header is used but not the .cp file
    'UProfiler.cp',
    'UQuickTime.cp',
    'UResourceMgr.cp',
    'UStandardFile.cp',
    'UTEViewTextAction.cp',
])

include_dirs = [
    ':libs:msl_c_headers:Public Includes',
    ':libs:msl_cpp_headers:Language Support',
    ':libs:msl_cpp_headers:Library Support',
    ':libs:Headers:Universal Headers',
    ':libs:PowerPlant:PowerPlant Headers'
]
source_files = []
object_files = []

for dirname in pp_dirs:
    mac_dirname = dirname.replace('/', ':')
    include_dirs.append(f':libs:PowerPlant:{mac_dirname}')
    for filename in os.listdir(f'libs/PowerPlant/{dirname}'):
        if filename in excluded:
            continue
        if filename.endswith('.cp'):
            source_files.append(f':libs:PowerPlant:{mac_dirname}:{filename}')
            object_files.append('powerplant/' + filename[:-3] + '.o')

for filename in os.listdir('src'):
    # for now only
    if filename == 'T2Application.cpp':
        continue

    if filename.endswith('.cpp'):
        source_files.append(f':src:{filename}')
        object_files.append('t2/' + filename[:-4] + '.o')
    if filename.endswith('.cp'):
        source_files.append(f':src:{filename}')
        object_files.append('t2/' + filename[:-3] + '.o')

os.putenv('MWCIncludes', ':libs:Headers')

args.append('-i')
args.append(':src')
args.append('-i-')
for name in include_dirs:
    args.append('-i')
    args.append(name)
args.append('-nomf')
args.append('-RTTI')
args.append('on')
args.append('-bool')
args.append('on')
args.append('-traceback')
args.append('-opt')
args.append('off,peep')
args.append('-sym')
args.append('on')
args.append('-char')
args.append('signed')
args.append('-fp_contract')
args.append('on')
args.append('-d')
args.append('Debug_Throw')
args.append('-d')
args.append('Debug_Signal')
args.append('-d')
args.append('PP_NewClasses')
args.append('-o')

outputs = {}
errors = {}
done_objs = []
start_time = time.perf_counter()

def build_file(i, src, obj):
    print(f'[{i:03d}/{count:03d}] {src}...')
    my_args = args[:]
    my_args.append(':obj:' + obj)
    my_args.append(src)
    proc = subprocess.run(my_args, capture_output=True, encoding='utf-8')

    output = None
    if proc.stdout:
        output = proc.stdout.split('\n')
    error = None
    if proc.stderr:
        error = proc.stderr.split('\n')

    return (obj, output, error)

count = len(source_files)
with concurrent.futures.ThreadPoolExecutor(max_workers=8) as executor:
    futures = []
    for i, (src, obj) in enumerate(zip(source_files, object_files)):
        # should check mtime!
        if not os.path.exists(f'obj/{obj}'):
            futures.append(executor.submit(build_file, i, src, obj.replace('/', ':')))

    for future in concurrent.futures.as_completed(futures):
        obj, output, error = future.result()
        done_objs.append(obj)
        if output:
            outputs[obj] = output
        if error:
            errors[obj] = error


end_time = time.perf_counter()

time_taken = end_time - start_time
print(f'Compiled in {time_taken:.2f} seconds')

with open('results.json', 'w') as f:
    results = dict(
        outputs=outputs,
        errors=errors,
        done_objs=done_objs,
        time_taken=time_taken
    )
    json.dump(results, f, indent=4, sort_keys=True)


