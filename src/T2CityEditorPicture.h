#pragma once

#include <LPane.h>

class T2GWorld;
class T2WorldPlugin;

class T2CityEditorPicture : public LPane {
public:
	T2CityEditorPicture(LStream *inStream);
	~T2CityEditorPicture();

	void SetPicture(T2WorldPlugin *plugin);
	void DrawSelf();

protected:
	T2GWorld *mGWorld;
};
