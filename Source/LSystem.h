#pragma once
#include "JuceHeader.h"

// Used to store generated L systems 
class LSystem
{
private:
	std::unordered_map<std::string, std::string> lSysRulemap;
	std::string axiom;
	std::string genString;
public:
	LSystem(std::string axiom, std::unordered_map<std::string, std::string> lsysRulesets)
		: axiom(axiom), lSysRulemap(lsysRulesets)
	{
		DBG("Created lSystem");
		DBG("Initial Axiom: " << axiom);
		DBG("RuleMap-----");
		for (const auto& [key, value] : lSysRulemap)
		{
			DBG("Key: " << key << " Value: " << value << "\n");
		}
		DBG("--------");
	}
	// For N generations, will go through each character and if it matches a key, appends value to string stream.
	// If no match found, just adds the same character. At the end, 'moves' the value to genString.
	
	// TODO: gens is always 0 for some reason.
	void generate(const std::atomic<float>& gens)
	{
		DBG("GENERATING L STRING");
		genString = axiom;
		DBG("Initial String: " << genString);
		// For each generation...
		for (int i = 0; i < gens; ++i)
		{
			// Search through each character and check if it needs to convert to new character and do so accordingly.
			std::ostringstream nextGen;
			DBG("Gen: " << i << "----------");
			for (char c : genString)
			{
				DBG("Current genString: " << genString);
				DBG("Checking: " << c);
				if (lSysRulemap.find(std::string(1, c)) != lSysRulemap.end())
				{
					DBG("Found " << c << " in ruleMap. Replacing with: " << lSysRulemap[std::string(1,c)]);
					nextGen << lSysRulemap.at(std::string(1, c));
				}
				else
				{
					DBG("Could not find " << c << " in ruleMap.");
					DBG("Adding: " << c);
					nextGen << c;
				}
				genString = std::move(nextGen.str());
			}
		}
		DBG("Final String: " << genString << "<----");
	}
};