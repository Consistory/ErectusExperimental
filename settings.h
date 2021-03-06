#pragma once
#include <map>
#include <Windows.h>
#include <string>
#include <unordered_map>

#include "common.h"

struct InfoBoxSettings
{
	bool drawLocalPlayerInfo;
	bool drawScrapLooterStatus;
	bool drawItemLooterStatus;
	bool drawNpcLooterStatus;
	bool drawContainerLooterStatus;
	bool drawHarvesterStatus;
	bool drawPositionSpoofingStatus;
	bool drawNukeCodes;
};
struct LooterSettings
{
	enum class Mode
	{
		Disabled,
		Auto,
		Keybind,
	} mode{};

	struct Looters {
		bool npcs;
		bool items;
		bool containers;
		bool flora;
	} looters{};

	struct Selection {
		struct WeaponsAndArmor
		{
			bool all;
			bool oneStar;
			bool twoStar;
			bool threeStar;

			[[nodiscard]] bool IsEnabled() const { return all || oneStar || twoStar || threeStar; }
		} weapons{}, apparel{};

		struct Aid
		{
			bool all;
			bool magazines;
			bool bobbleheads;

			[[nodiscard]] bool IsEnabled() const { return all || magazines || bobbleheads; }
		} aid{};

		struct Misc
		{
			bool all;

			[[nodiscard]] bool IsEnabled() const { return all; }
		} misc{};

		struct Holo
		{
			bool all;

			[[nodiscard]] bool IsEnabled() const { return all; }
		} holo{};

		struct Notes
		{
			bool all;
			bool treasureMaps;
			bool plansKnown;
			bool plansUnknown;

			[[nodiscard]] bool IsEnabled() const { return all || treasureMaps || plansKnown || plansUnknown; }
		} notes{};

		struct Junk
		{
			bool all;

			std::unordered_map<DWORD, bool>	components = []() {
				std::unordered_map<DWORD, bool> result(JUNK_COMPONENT_NAMES.size());
				for (const auto& component : JUNK_COMPONENT_NAMES)
					result.emplace(component.first, false);
				return result;
			}();

			[[nodiscard]] bool IsEnabled() const { return all || std::find_if(components.begin(), components.end(), [](const auto& element) { return element.second == true; }) != components.end(); }
		} junk{};

		struct Flora
		{
			bool all;

			std::unordered_map<DWORD, bool>	components = []() {
				std::unordered_map<DWORD, bool> result(FLORA_COMPONENT_NAMES.size());
				for (const auto& component : FLORA_COMPONENT_NAMES)
					result.emplace(component.first, false);
				return result;
			}();

			[[nodiscard]] bool IsEnabled() const { return all || std::find_if(components.begin(), components.end(), [](const auto& element) { return element.second == true; }) != components.end(); }
		} flora{};

		struct Mods
		{
			bool all;

			[[nodiscard]] bool IsEnabled() const { return all; }
		} mods{};

		struct Ammo
		{
			bool all;

			[[nodiscard]] bool IsEnabled() const { return all; }
		} ammo{};

		struct Other
		{
			bool caps;

			[[nodiscard]] bool IsEnabled() const { return caps; }
		} other{};

		std::map<DWORD, bool> whitelist, blacklist;

		[[nodiscard]] bool IsEnabled() const {
			return weapons.IsEnabled()
				|| apparel.IsEnabled()
				|| aid.IsEnabled()
				|| misc.IsEnabled()
				|| holo.IsEnabled()
				|| notes.IsEnabled()
				|| junk.IsEnabled()
				|| flora.IsEnabled()
				|| mods.IsEnabled()
				|| ammo.IsEnabled()
				|| other.IsEnabled()
				|| std::find_if(whitelist.begin(), whitelist.end(), [](const auto& element) { return element.second == true; }) != whitelist.end()
				|| std::find_if(blacklist.begin(), blacklist.end(), [](const auto& element) { return element.second == true; }) != blacklist.end();
		}
	} selection;
};
struct EspSettings
{
	struct Actors
	{
		bool enabled = true;
		int enabledDistance = 1500;
		bool drawAlive = true;
		float aliveColor[3] = { 0.0f, 1.0f, 0.0f };
		bool drawDowned = true;
		float downedColor[3] = { 1.0f, 1.0f, 0.0f };
		bool drawDead = false;
		float deadColor[3] = { 1.0f, 0.0f, 0.0f };
		bool drawUnknown = false;
		float unknownColor[3] = { 1.0f, 0.5f, 0.0f };
		bool drawEnabled = true;
		float enabledAlpha = 1.f;
		bool drawDisabled = false;
		float disabledAlpha = 0.5f;
		bool drawNamed = true;
		bool drawUnnamed = false;
		bool showName = true;
		bool showDistance = true;
		bool showHealth = true;
		bool showDeadHealth = false;
	} players, npcs;

	struct Items
	{
		bool enabled = false;
		int enabledDistance = 1500;
		float color[3] = { 1.0f, 1.0f, 1.0f };
		bool drawEnabled = true;
		float enabledAlpha = 1.f;
		bool drawDisabled = false;
		float disabledAlpha = 0.5f;
		bool drawNamed = true;
		bool drawUnnamed = false;
		bool showName = true;
		bool showDistance = true;
	} junk, containers, plans, magazines, bobbleheads, items, flora, entities;

	struct LegendaryNpcs
	{
		bool overrideLivingOneStar = true;
		float livingOneStarColor[3] = { 0.7f, 1.0f, 0.7f };
		bool overrideDeadOneStar = true;
		float deadOneStarColor[3] = { 1.0f, 0.5f, 0.5f };
		bool overrideLivingTwoStar = true;
		float livingTwoStarColor[3] = { 0.7f, 1.0f, 0.7f };
		bool overrideDeadTwoStar = true;
		float deadTwoStarColor[3] = { 1.0f, 0.5f, 0.5f };
		bool overrideLivingThreeStar = true;
		float livingThreeStarColor[3] = { 0.7f, 1.0f, 0.7f };
		bool overrideDeadThreeStar = true;
		float deadThreeStarColor[3] = { 1.0f, 0.5f, 0.5f };
	} legendaryNpcs;

	struct FluxSettings
	{
		bool crimsonFluxEnabled = true;
		bool cobaltFluxEnabled = true;
		bool yellowcakeFluxEnabled = true;
		bool fluorescentFluxEnabled = true;
		bool violetFluxEnabled = true;
	} flux{};

	struct KnownRecipeSettings
	{
		bool knownRecipesEnabled = true;
		bool unknownRecipesEnabled = true;
	} recipes;

	std::map<DWORD, bool> whitelist, blacklist;
};

//utils
class WeaponSettings
{
public:
	bool noRecoil;
	bool noSpread;
	bool noSway;
	bool infiniteAmmo;
	bool instantReload;
	bool automaticflag;
	bool capacityEnabled;
	int capacity;
	bool speedEnabled;
	float speed;
	bool reachEnabled;
	float reach;
};
class TargetSettings
{
public:
	bool lockPlayers = false;
	bool lockNpCs = true;
	bool indirectPlayers = false;
	bool indirectNpCs = true;
	bool directPlayers = false;
	bool directNpCs = true;
	bool targetLiving = false;
	bool targetDowned = false;
	bool targetDead = false;
	bool targetUnknown = false;
	bool ignoreRenderDistance = false;
	float lockingFov = 20.0f;
	bool ignoreEssentialNpCs = true;
	float lockingColor[3] = { 1.0f, 0.0f, 1.0f };
	bool retargeting = false;
	int cooldown = 1;
	int sendDamageMin = 1;
	int sendDamageMax = 1;
	int favoriteIndex = 12;
};
class LocalPlayerSettings
{
public:
	bool positionSpoofingEnabled = false;
	int positionSpoofingHeight = 524287;
	bool noclipEnabled = false;
	float noclipSpeed = 0.1f;
	bool clientState = false;
	bool automaticClientState = false;
	bool freezeApEnabled = false;
	bool actionPointsEnabled = false;
	int actionPoints = 9001;
	bool strengthEnabled = false;
	int strength = 9001;
	bool perceptionEnabled = false;
	int perception = 9001;
	bool enduranceEnabled = false;
	int endurance = 9001;
	bool charismaEnabled = false;
	int charisma = 9001;
	bool intelligenceEnabled = false;
	int intelligence = 9001;
	bool agilityEnabled = false;
	int agility = 9001;
	bool luckEnabled = false;
	int luck = 9001;
};
class OpkSettings
{
public:
	bool playersEnabled;
	bool npcsEnabled;
};
class UtilitySettings
{
public:
	bool debugEsp;
	DWORD ptrFormId;
	DWORD addressFormId;
};
class SwapperSettings
{
public:
	DWORD sourceFormId;
	DWORD destinationFormId;
};
class TransferSettings
{
public:
	DWORD sourceFormId = 0;
	DWORD destinationFormId = 0;
	bool useWhitelist = true;
	bool useBlacklist = true;
	bool whitelisted[32] = {};
	DWORD whitelist[32] = {};
	bool blacklisted[32] = {
		true, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false,
	};
	DWORD blacklist[32] = {
		0x00021B3B, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	};
};
class TeleportEntry
{
public:
	float destination[4];
	DWORD cellFormId;
	bool disableSaving;
};
class TeleportSettings
{
public:
	TeleportEntry entries[16];
};
class NukeCodeSettings
{
public:
	bool automaticNukeCodes;
};
class MeleeSettings
{
public:
	bool enabled;
	int speedMin;
	int speedMax;
};
class ChargenSettings
{
public:
	bool enabled;
	float thin;
	float muscular;
	float large;
};
class MessageWriterSettings
{
public:
	bool enabled;
};

class Settings final {
public:
	static void Read();
	static void Write();

	inline static EspSettings esp = {};
	inline static LooterSettings looter = {};
	inline static InfoBoxSettings infobox = {};
	inline static MessageWriterSettings msgWriter = {};

	//utils
	static WeaponSettings weapons;
	inline static TargetSettings targetting = {};
	inline static LocalPlayerSettings localPlayer = {};
	inline static OpkSettings opk = {};
	inline static UtilitySettings utilities = {};
	inline static SwapperSettings swapper = {};
	inline static TransferSettings customTransferSettings = {};
	inline static TeleportSettings teleporter = {};
	inline static NukeCodeSettings customNukeCodeSettings = {};
	inline static MeleeSettings melee = { false,10,20 };
	inline static ChargenSettings characterEditor = { false,0.33f,0.33f,0.33f };
	inline static WeaponSettings defaultWeaponSettings{
		false, false, false, false, false, false, false, 250, false, 2.0f, false, 500.0f
	};

private:
	static void GetItemSettings(const std::string& section, EspSettings::Items& value, const EspSettings::Items& deflt);
	static void SetItemSettings(const std::string& section, EspSettings::Items& value, const EspSettings::Items& deflt);

	static void GetEspSettings();
	static void SetEspSettings();
	static void GetInfoBoxSettings();
	static void SetInfoBoxSettings();
	static void GetLooterSettings();
	static void SetLooterSettings();

	static void GetWeaponSettings();
	static void SetWeaponSettings();
	static void GetTargetSettings();
	static void SetTargetSettings();
	static void GetLocalPlayerSettings();
	static void SetLocalPlayerSettings();
	static void GetOpkSettings();
	static void SetOpkSettings();
	static void GetUtilitySettings();
	static void SetUtilitySettings();
	static void GetSwapperSettings();
	static void SetSwapperSettings();
	static void GetTransferSettings();
	static void SetTransferSettings();
	static void GetTeleportSettings();
	static void SetTeleportSettings();
	static void GetNukeCodeSettings();
	static void SetNukeCodeSettings();
	static void GetLegendarySettings();
	static void SetLegendarySettings();
	static void GetFluxSettings();
	static void SetFluxSettings();
	static void GetKnownRecipeSettings();
	static void SetKnownRecipeSettings();
	static void GetMeleeSettings();
	static void SetMeleeSettings();
	static void GetChargenSettings();
	static void SetChargenSettings();
	static void GetBitMsgWriterSettings();
	static void SetBitMsgWriterSettings();
	
	static void GetDword(const std::string& section, const std::string& key, DWORD& value, DWORD deflt);
	static void SetDword(const std::string& section, const std::string& key, DWORD value, DWORD deflt);
	static void GetInt(const std::string& section, const std::string& key, int& value, int deflt);
	static void SetInt(const std::string& section, const std::string& key, int value, int deflt);
	static void GetSliderInt(const std::string& section, const std::string& key, int& value, int deflt, int min, int max);
	static void SetSliderInt(const std::string& section, const std::string& key, int& value, int deflt, int min, int max);
	static void GetFloat(const std::string& section, const std::string& key, float& value, float deflt);
	static void SetFloat(const std::string& section, const std::string& key, float value, float deflt);
	static void GetSliderFloat(const std::string& section, const std::string& key, float& value, float deflt, float min, float max);
	static void SetSliderFloat(const std::string& section, const std::string& key, float& value, float deflt, float min, float max);
	static void GetRgb(const std::string& section, const std::string& key, float* value, const float* deflt);
	static void SetRgb(const std::string& section, const std::string& key, float* value, const float* deflt);
	static void GetQuadFloat(const std::string& section, const std::string& key, float* value, const float* deflt);
	static void SetQuadFloat(const std::string& section, const std::string& key, float* value, const float* deflt);
	static void GetBool(const std::string& section, const std::string& key, bool& value, bool deflt);
	static void SetBool(const std::string& section, const std::string& key, const bool& value, bool deflt);
	static void GetActorSettings(const std::string& section, EspSettings::Actors& value, const EspSettings::Actors& deflt);
	static void SetActorSettings(const std::string& section, EspSettings::Actors& value, const EspSettings::Actors& deflt);

	virtual void Dummy() = 0;
};