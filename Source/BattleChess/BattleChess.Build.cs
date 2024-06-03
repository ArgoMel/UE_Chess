using UnrealBuildTool;

public class BattleChess : ModuleRules
{
	public BattleChess(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore" ,
			"EnhancedInput"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
