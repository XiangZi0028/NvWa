#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FStandardHeadShapeTypeActions;
class FStandardBodyShapeTypeActions;
class FNvWaEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
private:
    TSharedPtr<FStandardHeadShapeTypeActions> StandardHeadShapeTypeActions;
    TSharedPtr<FStandardBodyShapeTypeActions> StandardBodyShapeTypeActions;
};
