#include "NPCGraphDataAsset.h"

const FNPCGraphNode* UNPCGraphDataAsset::FindNode(FName NPCID) const
{
	for (const FNPCGraphNode& Node : Nodes)
	{
		if (Node.NPCID == NPCID)
		{
			return &Node;
		}
	}
	return nullptr;
}

void UNPCGraphDataAsset::BuildReflectionReveal()
{
	ReflectionReveal = TEXT("What each of them held of whoever left:\n\n");
	for (const FNPCGraphNode& Node : Nodes)
	{
		if (!Node.NPCName.IsEmpty() && !Node.HiddenTitle.IsEmpty())
		{
			ReflectionReveal += FString::Printf(TEXT("%s: %s.\n"), *Node.NPCName, *Node.HiddenTitle);
		}
	}
}
