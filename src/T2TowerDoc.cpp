#include "T2Application.h"
#include "T2TowerDoc.h"

T2TowerDoc::T2TowerDoc(T2Application *app, FSSpec *ignored, T2WorldPlugin *worldPlugin)
	: T2Document(app, ignored, 1)
{
	// lots of stuff here.
}

void T2TowerDoc::Initialize() {}
T2TowerDoc::~T2TowerDoc() {}
void T2TowerDoc::InitDocumentForPlugins(T2WorldPlugin *worldPlugin) {}
void T2TowerDoc::InitDocument() {}
Boolean T2TowerDoc::CheckFinger(T2MoverDef *moverDef, Point pt, Boolean flag) {}
void T2TowerDoc::DoMessage(Point pt, LStr255 str) {}
void T2TowerDoc::DoMessage(Point pt, ResIDT strID) {}
Boolean T2TowerDoc::IsToiletFlagOn() const {}
Boolean T2TowerDoc::IsColdFlagOn() const {}
Boolean T2TowerDoc::IsRectInView(const Rect &rect) {}
void T2TowerDoc::LoadSecretItem(Int16 item) {}
Int32 T2TowerDoc::Get1stCinemaDate() {}
void T2TowerDoc::Set1stCinemaDate(Int32 date) {}
Boolean T2TowerDoc::Start() {}
Boolean T2TowerDoc::Pause() {}
void T2TowerDoc::Step() {}
void T2TowerDoc::DrawSpeedChanged() {}
void T2TowerDoc::SetDrawSpeed(Int16 speed) {}
Boolean T2TowerDoc::SetElevTransparent(Boolean value) {}
Boolean T2TowerDoc::SetVolatile(Boolean value) {}
void T2TowerDoc::AdjustNextSimulationTime() {}
void T2TowerDoc::UnloadPlugins() {}
Int32 T2TowerDoc::GetCategoryCount() {}
Int32 T2TowerDoc::GetUsingToolDefList(Int32 index) const {}
Int32 T2TowerDoc::GetToolDefListByCategory(Int16 category) {}

T2TowerDoc *T2TowerDoc::GetCurrentT2TowerDoc() {}

void T2TowerDoc::ClearDocumentForPlugins() {}
CFilePluginList *T2TowerDoc::GetTenantPlugins() {}
CFilePluginList *T2TowerDoc::GetMoverPlugins() {}
void T2TowerDoc::SpendTime(const EventRecord &event) {}
void T2TowerDoc::IdleSimulation() {}
void T2TowerDoc::IdleWorld() {}
void T2TowerDoc::AttemptClose(Boolean flag) {}
Boolean T2TowerDoc::AttemptQuitSelf(Int32 saveOption) {}
Boolean T2TowerDoc::ObeyCommand(CommandT command, void *ioParam) {}
void T2TowerDoc::FindCommandStatus(CommandT inCommand, Boolean &outEnabled, Boolean &outUsesMark, Char16 &outMark, Str255 outName) {}
void T2TowerDoc::DbgFloorInfo(const SMouseDownEvent &event) {}
void T2TowerDoc::DoPayTool(Int32 a, Int16 b, T2ToolDef *toolDef) {}
void T2TowerDoc::DoPayTool(Int32 a, Int16 b, T2ToolDef *toolDef, const LString &str, Int16 c, Int16 d) {}
void T2TowerDoc::DoPay(Int32 a, Int16 b) {}
void T2TowerDoc::UpdateFundsInfo() {}
Int32 T2TowerDoc::GetCurrentFunds() const {}
void T2TowerDoc::DoDestruct(const SMouseDownEvent &event) {}
void T2TowerDoc::DoGetInfo(const SMouseDownEvent &event) {}
void T2TowerDoc::DoInterview(Point pt) {}
void T2TowerDoc::DoFingerTool(const SMouseDownEvent &event) {}
void T2TowerDoc::DoFingerMachine(T2MoverDef *moverDef, T2Mover *mover, Point pt, Int16 a) {}
void T2TowerDoc::DoSearchRangeTool(const SMouseDownEvent &event) {}
void T2TowerDoc::SetSearchRangeFrom(T2Tenant *tenant) {}
void T2TowerDoc::DoClickByTenantTool(const SMouseDownEvent &event, T2TenantDef *tenantDef, UInt32 a) {}
void T2TowerDoc::DoDragByTenantTool(Rect rect, Int16 &s) {}
void T2TowerDoc::DoReleaseByTenantTool(Rect rect) {}
void T2TowerDoc::DoClickByMoverTool(const SMouseDownEvent &event, T2MoverDef *moverDef, UInt32 a) {}
void T2TowerDoc::DoClickByOutObjTool(const SMouseDownEvent &event, T2OutObjDef *outObjDef, UInt32 a) {}
Boolean T2TowerDoc::OutsideAreaCheck(T2Tenant *tenant, Boolean showErr) {}
Boolean T2TowerDoc::DestructTenant(Point ptA, Point ptB, T2Tenant *tenant, Boolean soundFlag) {}
Boolean T2TowerDoc::DestructMover(Point ptA, Point ptB, T2Mover *mover) {}
Boolean T2TowerDoc::DestructOutObj(Point ptA, Point ptB, T2OutObj *outObj) {}
Boolean T2TowerDoc::BuildTenant(Rect rect, Int16 a, Boolean flag) {}
void T2TowerDoc::TenantAdded(T2Tenant *tenant) {}
void T2TowerDoc::TenantRemoved(T2Tenant *tenant) {}
Boolean T2TowerDoc::BuildMover(const Rect &rect, T2MoverDef *moverDef) {}
Boolean T2TowerDoc::AddModule(const Rect &rect, T2MoverDef *moverDef) {}
void T2TowerDoc::BuildOutObj(const Rect &rect, T2OutObjDef *outObjDef) {}
void T2TowerDoc::SelectPlugins(Int16 a, Boolean flag) {}
void T2TowerDoc::FinalEventOccur() {}
Int32 T2TowerDoc::CheckGameLevel() {}
GrafPtr T2TowerDoc::GetMacPort() {}
void T2TowerDoc::UpdateAllTenant() {}
void T2TowerDoc::DrawBkgnd(const Rect &rect) {}
void T2TowerDoc::DrawBuilding(const Rect &rect1, const Rect &rect2) {}
void T2TowerDoc::DrawOutView(const Rect &rect) {}
void T2TowerDoc::DrawInView(const Rect &rect1, const Rect &rect2) {}
void T2TowerDoc::DrawTenantOutViewAll(const Rect &rect) {}
void T2TowerDoc::DrawTenantAll(const Rect &rect1, const Rect &rect2) {}
void T2TowerDoc::DrawRequestAll(const Rect &rect) {}
void T2TowerDoc::DrawMoverAll(const Rect &rect) {}
void T2TowerDoc::DrawTenantAllWithBG(const Rect &rect) {}
void T2TowerDoc::DrawSideObject(Point ptA, Point ptB, const Rect &rect) {}
void T2TowerDoc::DrawTenantAllWithoutBG(const Rect &rect) {}
void T2TowerDoc::DrawMWDispatch(T2MWDispatchButton *button) {}
void T2TowerDoc::DrawOutObject(const Rect &rect) {}
void T2TowerDoc::InvalClock() {}
void T2TowerDoc::InvalCalender() {}
void T2TowerDoc::InvalFunds() {}
void T2TowerDoc::InvalPopulation() {}
void T2TowerDoc::InvalMessage() {}
void T2TowerDoc::InvalByPaneID(Int32 id) {}
Boolean T2TowerDoc::DoGetInfoTenant(const SMouseDownEvent &event, T2Tenant *tenant) {}
Boolean T2TowerDoc::DoGetInfoMover(const SMouseDownEvent &event, T2Mover *mover) {}
Boolean T2TowerDoc::DoGetInfoPeople(const SMouseDownEvent &event, T2People *people) {}
Boolean T2TowerDoc::DoGetInfotheOutObj(const SMouseDownEvent &event, T2OutObj *outObj) {}
void T2TowerDoc::DoFind(T2Name *name) {}
void T2TowerDoc::DoRenumberTenant() {}
Int16 T2TowerDoc::GetNextTenantNumber(Int16 num) {}
void T2TowerDoc::CalcDragMask(Rect &rect, Boolean flag) {}
void T2TowerDoc::CalcDragMaskPoint(Rect &rect, Int32 &l, DragMask *dragMask, Int16 a, Boolean showErr) {}
Boolean T2TowerDoc::CheckTenantArea(Rect &rect, Boolean showErr, Boolean anotherFlag) {}
T2Tenant *T2TowerDoc::AssignNewTenant(T2TenantDef *tenantDef, Rect &rect, UInt32 ul) {}
void T2TowerDoc::CheckBuildQueue() {}
Boolean T2TowerDoc::CheckFillFloor(Rect &rect, UInt32 &ul1, UInt32 &ul2) {}
void T2TowerDoc::FillFloor(Rect rect) {}
Int32 T2TowerDoc::GetFloorVariation() const {}
Boolean T2TowerDoc::IsSkyBridge(T2TenantDef *tenantDef) {}
void T2TowerDoc::BreakoutEmergency() {}
void T2TowerDoc::DoAESave(FSSpec &spec, OSType type) {}
void T2TowerDoc::DoSave() {}
void T2TowerDoc::OpenFile(FSSpec &spec) {}
CPluginInfoArray *T2TowerDoc::MakeLackPluginArray(T2BufferedFileStream *stream) {}
Boolean T2TowerDoc::CheckMustPlugin(LArray *array) {}
Boolean T2TowerDoc::CheckLackPlugin(LArray *array) {}
void T2TowerDoc::NewDocument() {}
void T2TowerDoc::ReadPool(LStream &stream) {}
T2GWorld *T2TowerDoc::GetCategoryIcon(Int16 category) {}
Boolean T2TowerDoc::GetCategoryName(Int16 category, LStr255 &str) {}
T2GWorld *T2TowerDoc::GetCategoryHelp(Int16 category) {}
void T2TowerDoc::SetWalkRate(Int16 walkRate) {}
void T2TowerDoc::SetViewMode(Int16 viewMode) {}
Boolean T2TowerDoc::FindToolStatus(Int16 what) const {}
Boolean T2TowerDoc::FindCategoryStatus(Int16 category) const {}
CPluginInfoArray *T2TowerDoc::MakePluginInfoArray() {}
void T2TowerDoc::_MakePluginInfoArray(CPluginInfoArray *pia, LArray *array) {}
Boolean T2TowerDoc::PluginCheck(LArray *array) {}
void T2TowerDoc::CalcCraneUpdateRect(Rect &rect) {}
void T2TowerDoc::DisplayGraphWindow() {}
void T2TowerDoc::SetWorldStatistics(void *stats) {}
void T2TowerDoc::DisplaySettlementWindow() {}
void T2TowerDoc::AddFavoritePeople(T2People *people) {}
void T2TowerDoc::AddFavoriteTenant(T2Tenant *tenant) {}
void T2TowerDoc::RemoveFavoriteName(T2Name *name, Boolean flag) {}
void T2TowerDoc::RemoveFavoritePeople(const LString &str, Boolean flag) {}
void T2TowerDoc::RemoveFavoriteTenant(const LString &str, Boolean flag) {}
void T2TowerDoc::RemoveFavoritePeople(T2People *people, Boolean flag) {}
void T2TowerDoc::RemoveFavoriteTenant(T2Tenant *tenant, Boolean flag) {}
void T2TowerDoc::OpenRemoveFavoritePeopleDialog() {}
void T2TowerDoc::OpenRemoveFavoriteTenantDialog() {}
void T2TowerDoc::UpdateFavoriteMenus(Boolean flag) {}
void T2TowerDoc::RecreateFavoriteMenus() {}
void T2TowerDoc::RequestPluginDialog(T2PluginDialog *dialog) {}
void T2TowerDoc::DoPluginDialog(void *param) {}
Boolean T2TowerDoc::IsFloatingInitialVisible(CommandT command) {}
void T2TowerDoc::DoEmergency() {}
