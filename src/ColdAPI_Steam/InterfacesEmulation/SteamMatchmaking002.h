#pragma once
#include "../public SDK/ISteamMatchmaking002.h"
#include "../Bridge.h"


class SteamMatchmakingIn002 : public ISteamMatchmaking002
{
public:
	int GetFavoriteGameCount()
	{
		return 0;
	}

	bool GetFavoriteGame(int iGame, uint32* pnAppID, uint32* pnIP, uint16* pnConnPort, uint16* pnQueryPort, uint32* punFlags, RTime32* pRTime32LastPlayedOnServer)
	{
		return false;
	}

	int AddFavoriteGame(uint32 nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, RTime32 rTime32LastPlayedOnServer)
	{
		return NULL;
	}

	bool RemoveFavoriteGame(uint32 nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags)
	{
		return false;
	}

	void RequestLobbyList()
	{
		return;
	}
	CSteamID GetLobbyByIndex(int iLobby)
	{
		CSteamID idata = CSteamID(1111111, 0x40000, k_EUniversePublic, k_EAccountTypeChat);
		return idata;
	}
	void CreateLobby(bool bPrivate)
	{
		LobbyCreated_t* Response = nullptr;
		CSteamID ID = CSteamID(1337132, 0x40000, k_EUniversePublic, k_EAccountTypeChat);		// Init a CSteamID structure

		auto RequestID = SteamCallback::RegisterCall(true);

		Response = static_cast<LobbyCreated_t*>(malloc(sizeof(LobbyCreated_t)));		// alloc memory to set a new fake Lobby response
		Response->m_eResult = k_EResultOK;
		Response->m_ulSteamIDLobby = ID.ConvertToUint64();

		SteamCallback::CreateNewRequest(Response, sizeof(*Response), Response->k_iCallback, RequestID);
		JoinLobby(ID);
	}
	void JoinLobby(CSteamID steamIDLobby)
	{
		LobbyEnter_t* Response = nullptr;

		auto RequestID = SteamCallback::RegisterCall(true);
		Response = static_cast<LobbyEnter_t*>(malloc(sizeof(LobbyEnter_t)));
		Response->m_bLocked = false;
		Response->m_EChatRoomEnterResponse = k_EChatRoomEnterResponseSuccess;
		Response->m_rgfChatPermissions = (EChatPermission)0xFFFFFFFF;
		Response->m_ulSteamIDLobby = steamIDLobby.ConvertToUint64();

		SteamCallback::CreateNewRequest(Response, sizeof(*Response), Response->k_iCallback, RequestID);
	}
	void LeaveLobby(CSteamID steamIDLobby)
	{
		auto RequestID = SteamCallback::RegisterCall(true);

		LobbyChatUpdate_t* retvals = (LobbyChatUpdate_t*)malloc(sizeof(LobbyChatUpdate_t));
		retvals->m_rgfChatMemberStateChange = EChatMemberStateChange::k_EChatMemberStateChangeLeft;
		retvals->m_ulSteamIDLobby = steamIDLobby;
		retvals->m_ulSteamIDMakingChange = Steam_Config::UserID;
		retvals->m_ulSteamIDUserChanged = Steam_Config::UserID;
		SteamCallback::CreateNewRequest(retvals, sizeof(*retvals), retvals->k_iCallback, RequestID);
	}
	bool InviteUserToLobby(CSteamID steamIDLobby, CSteamID steamIDInvitee)
	{
		return false;
	}
	int GetNumLobbyMembers(CSteamID steamIDLobby)
	{
		return 1;
	}
	CSteamID GetLobbyMemberByIndex(CSteamID steamIDLobby, int iMember)
	{
		return CSteamID((uint64)Steam_Config::UserID);
	}
	const char* GetLobbyData(CSteamID SteamIDLobby, const char* pchKey)
	{
		return "";
	}
	bool SetLobbyData(CSteamID steamIDLobby, const char* pchKey, const char* pchValue)
	{
		return false;
	}
	const char* GetLobbyMemberData(CSteamID steamIDLobby, CSteamID steamIDUser, const char* pchKey)
	{
		return "";
	}
	void SetLobbyMemberData(CSteamID steamIDLobby, const char* pchKey, const char* pchValue)
	{
		return;
	}
	bool SendLobbyChatMsg(CSteamID steamIDLobby, const void* pvMsgBody, int cubMsgBody)
	{
		return false;
	}
	int GetLobbyChatEntry(CSteamID steamIDLobby, int iChatID, CSteamID* pSteamIDUser, void* pvData, int cubData, EChatEntryType* peChatEntryType)
	{
		return NULL;
	}

	bool RequestLobbyData(CSteamID steamIDLobby)
	{
		return false;
	}

	void SetLobbyGameServer(CSteamID steamIDLobby, uint32 unGameServerIP, uint16 unGameServerPort, CSteamID steamIDGameServer)
	{
		return;
	}
};
