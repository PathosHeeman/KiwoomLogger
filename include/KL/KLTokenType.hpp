#pragma once
#ifndef __KL_TOKEN_TYPE_HPP__
#define __KL_TOKEN_TYPE_HPP__

#include <string>
#include <unordered_map>

namespace KiwoomLogger
{
	enum KLTokenType
	{
		KL_TOKEN_COMMA,
		KL_TOKEN_COLON,
		KL_TOKEN_SEMICOLON,
		KL_TOKEN_COMMAND,
		KL_TOKEN_COMMAND_IDENTIFIER,
		KL_TOKEN_LEFT_PAREN,
		KL_TOKEN_RIGHT_PAREN,
		KL_TOKEN_EOF
	};

	enum KLCommandType
	{
		KL_CT_START,
		KL_CT_EXIT,
		KL_CT_ITEM_ADD,
		KL_CT_ITEM_CLEAR,
		KL_CT_ITEM_PRINT,
		KL_CT_ITEM_NONE
	};
	static const wchar_t* CommandStr[] = 
	{
		L"KL",
		L"exit",
		L"item_add",
		L"item_clear",
		L"item_print"
	};
	static_assert(sizeof(CommandStr) / sizeof(wchar_t*) == KL_CT_ITEM_NONE, "Wrong Setting for Command enum and strings");

	static const size_t TokenStringSize = 512;
	struct KLToken
	{
		KLTokenType tokenType;
		KLCommandType commandType;
		wchar_t string[TokenStringSize] = { 0, };
	};

	enum KLTokenErrorType
	{
		KL_ERR_UNVALID_TOKEN,
		KL_ERR_TOKEN_NONE
	};
	static const wchar_t* TokenErrorMessages[] =
	{
		L"��ȿ���� ���� ��ū�Դϴ�",
	};
	static_assert(sizeof(TokenErrorMessages) / sizeof(wchar_t*) == KL_ERR_TOKEN_NONE, "Wrong Setting for Token Error Type");

	enum KLCommandErrorType
	{
		KL_ERR_UNVALID_COMMAND_START,
		KL_ERR_UNVALID_COMMAND_END,
		KL_ERR_UNVALID_COMMAND,
		KL_ERR_UNVALID_COMMAND_ITEM_ADD,
		KL_ERR_UNVALID_COMMAND_ITEM_CLEAR,
		KL_ERR_UNVALID_COMMAND_ITEM_PRINT,
		KL_ERR_UNVALID_COMMAND_EXIT,
		KL_ERR_COMMAND_NONE
	};
	static const wchar_t* CommandErrorMessae[] =
	{
		L"��� �տ� KL�� ����ϼ���",
		L"��� ���� ';'�� ����ϼ���",
		L"��ȿ���� ���� ��ɾ��Դϴ�",
		L"��ȿ���� ���� item_add ��ɾ� �Դϴ�",
		L"��ȿ���� ���� item_clear ��ɾ� �Դϴ�",
		L"��ȿ���� ���� item_print ��ɾ� �Դϴ�",
		L"��ȿ���� ���� exit ��ɾ� �Դϴ�"
	};
	static_assert(sizeof(CommandErrorMessae) / sizeof(wchar_t*) == KL_ERR_COMMAND_NONE, "Wrong Setting for KLCommandErrorType");

	// You should std::wstring for hash
	// const wchar_t* only use the pointer hash
	// because it does not have any specializtion template
	extern std::unordered_map<std::wstring, KLCommandType> CommandMap;
	extern std::unordered_map<KLCommandType, std::wstring> ReverseCommandMap;
	void InitCommandMap();
}



#endif