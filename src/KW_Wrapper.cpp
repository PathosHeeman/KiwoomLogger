#include "KW_Wrapper.hpp"

IMPLEMENT_DYNCREATE(KW_ActiveXWrapper, CWnd)

KW_OpenAPIContext::KW_OpenAPIContext()
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}

/*************** KW_OpenAPIDlg **********************/
//*******************************************************************/
// Function Name : DoDataExchange
// Function      : DDX/DDV�� ���� �� �Լ� ȣ��
// Param         : CDataExchange*	pDX
// Return        : void
// Create        : , 2014/06/02
// Comment       : DDX - ��Ʈ�Ѱ� ����������̿� ������ ��ȯ�ϴ� ����
//				 : DDV - ��������� ���� �� ���� ��ȿ�� üũ
//				 : UapdateData()�Լ��� ���� ȣ�� �� �� ����
//*******************************************************************/
void KW_OpenAPIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(KW_OpenAPIDlg)
	DDX_Control(pDX, IDC_KHOPENAPICTRL1, kw_openAPIContext.m_khOpenApi);
	//}}AFX_DATA_MAP
}

//*******************************************************************/
// BEGIN_MESSAGE_MAP
//*******************************************************************/
BEGIN_MESSAGE_MAP(KW_OpenAPIDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_SCRENN_CLOSE, OnScreenClose)
END_MESSAGE_MAP()

//*******************************************************************/
// BEGIN_EVENTSINK_MAP
//*******************************************************************/
BEGIN_EVENTSINK_MAP(KW_OpenAPIDlg, CDialogEx)
	ON_EVENT(KW_OpenAPIDlg, IDC_KHOPENAPICTRL1, 1, OnReceiveTrDataKhopenapictrl, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(KW_OpenAPIDlg, IDC_KHOPENAPICTRL1, 2, OnReceiveRealDataKhopenapictrl, VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(KW_OpenAPIDlg, IDC_KHOPENAPICTRL1, 3, OnReceiveMsgKhopenapictrl, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(KW_OpenAPIDlg, IDC_KHOPENAPICTRL1, 4, OnReceiveChejanData, VTS_BSTR VTS_I4 VTS_BSTR)
	ON_EVENT(KW_OpenAPIDlg, IDC_KHOPENAPICTRL1, 5, OnEventConnect, VTS_I4)
	ON_EVENT(KW_OpenAPIDlg, IDC_KHOPENAPICTRL1, 7, OnReceiveRealCondition, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(KW_OpenAPIDlg, IDC_KHOPENAPICTRL1, 8, OnReceiveTrCondition, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I2 VTS_I2)
	ON_EVENT(KW_OpenAPIDlg, IDC_KHOPENAPICTRL1, 9, OnReceiveConditionVer, VTS_I4 VTS_BSTR)
END_EVENTSINK_MAP()

BOOL KW_OpenAPIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	CString		strTitle;
	GetWindowText(strTitle);
	// strTitle += KL_VERSION_MAJOR;
	SetWindowText(strTitle);
	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	// OpenApi ���� ó��(�α��� â ����)
	kw_openAPIContext.m_khOpenApi.CommConnect();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void KW_OpenAPIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//*******************************************************************/
//! Function Name : OnDestroy
//! Function      : �ı���
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void KW_OpenAPIDlg::OnDestroy()
{

	// ��� ���� ó��
	kw_openAPIContext.m_khOpenApi.CommTerminate();
}

HCURSOR KW_OpenAPIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT KW_OpenAPIDlg::OnScreenClose(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case 0:
	{	
		char *cScrNo = (char*)lParam;
		CString strKey, strScrType;
		strKey.Format("%s", cScrNo);
		delete cScrNo;
		if (kw_openAPIContext.m_khOpenApi.GetSafeHwnd())
		{
			kw_openAPIContext.m_khOpenApi.DisconnectRealData(strKey);
		}
	}
	break;
	}

	return 0L;
}

void KW_OpenAPIDlg::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	if (!kw_openAPIContext.m_khOpenApi.GetSafeHwnd()) return;
}

void KW_OpenAPIDlg::OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg)
{
	if (!kw_openAPIContext.m_khOpenApi.GetSafeHwnd()) return;

}

void KW_OpenAPIDlg::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
	if (!kw_openAPIContext.m_khOpenApi.GetSafeHwnd()) return;
}

void KW_OpenAPIDlg::OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList)
{
	if (!kw_openAPIContext.m_khOpenApi.GetSafeHwnd()) return;

}

void KW_OpenAPIDlg::OnReceiveRealCondition(LPCTSTR strCode, LPCTSTR strType, LPCTSTR strConditionName, LPCTSTR strConditionIndex)
{
	if (!kw_openAPIContext.m_khOpenApi.GetSafeHwnd()) return;

}

void KW_OpenAPIDlg::OnReceiveTrCondition(LPCTSTR sScrNo, LPCTSTR strCodeList, LPCTSTR strConditionName, int nIndex, int nNext)
{
	if (!kw_openAPIContext.m_khOpenApi.GetSafeHwnd()) return;

}

void KW_OpenAPIDlg::OnReceiveConditionVer(long lRet, LPCTSTR sMsg)
{
	if (!kw_openAPIContext.m_khOpenApi.GetSafeHwnd()) return;

	if(lRet != 1)
	{// ����� ���ǰ˻��� ������û�� ������ �߻��� ���...
		CString		strErr; strErr.Format(_T("%s [%d]"), sMsg, lRet);
		AfxMessageBox(strErr);
		return;
	}
}

void KW_OpenAPIDlg::OnEventConnect(LONG nItemCnt)
{
	if (nItemCnt == 0)
	{
		// ���� ����ó��
	}
	else
	{
		// ���� ������ ó��
		EndDialog(IDCANCEL);
	}
}
/*************** KW_OpenAPIDlg **********************/

BOOL KW_OpenAPIContext::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�.
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));

	//////////////////////////////////////////////////////////////////
	// ���������� �н��� �����Ѵ�.
	char szPath[MAX_PATH];
	GetModuleFileName(AfxGetInstanceHandle(), szPath, MAX_PATH);
	*strrchr(szPath, '\\') = '\0';
	m_sAppPath = szPath;

	CString strFileName = m_sAppPath + "/data";
	if (!::PathIsDirectory(strFileName))		// ������ ���ٸ�
	{
		::CreateDirectory(strFileName, NULL);
	}

	KW_OpenAPIDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	return TRUE;
}

CString KW_OpenAPIContext::ConvertDataFormat(int nType, LPCTSTR szData, LPCTSTR szBeforeData, LPCTSTR szAfterData)
{
	CString strReturn, strData, strTemp = strData = szData;
	switch (nType)
	{
	case DT_DATE:			// ����
	{
		if (strTemp.GetLength() == 6)
		{
			strData.Format("%02s/%02s/%02s", strTemp.Left(2), strTemp.Mid(2, 2), strTemp.Right(2));
		}
		else if (strTemp.GetLength() == 8)
		{
			strData.Format("%04s/%02s/%02s", strTemp.Left(4), strTemp.Mid(4, 2), strTemp.Right(2));
		}
		break;
	}
	case DT_TIME:			// �ð�
	{
		if (strTemp.GetLength() == 6)
		{
			strData.Format("%02s:%02s:%02s", strTemp.Left(2), strTemp.Mid(2, 2), strTemp.Right(2));
		}
		else if (strTemp.GetLength() == 8)
		{
			strData.Format("%02s:%02s:%02s:%02s", strTemp.Left(2), strTemp.Mid(2, 2), strTemp.Mid(4, 2), strTemp.Right(2));
		}
		break;
	}
	
	case DT_NUMBER:			// ����
	case DT_ZERO_NUMBER:	// ����(0ǥ��)
	{
		strTemp.Replace("+", "");
		if (atof(strTemp) == 0.00)
		{
			strData = nType == DT_ZERO_NUMBER ? strTemp : "";
			break;
		}

		int nFind = strTemp.Find(".");
		if (nFind < 0)
		{
			strData = strTemp;
		}
		else
		{
			strData = strTemp.Left(nFind);
			strTemp = strTemp.Mid(nFind);
		}

		TCHAR szFormatData[1024] = { 0, };
		NUMBERFMT fmt = { 0, 0, 3, _T("."), _T(","), 1 };
		::GetNumberFormat(NULL, 0, strData, &fmt, szFormatData, 1024);

		if (nFind < 0)
		{
			nType == DT_ZERO_NUMBER ? strData.Format("%01s", szFormatData) : strData.Format("%s", szFormatData);
		}
		else
		{
			strData.Format("%01s%s", szFormatData, strTemp);
		}
		break;
	}
	}

	strReturn.Format("%s%s%s", szBeforeData, strData, szAfterData);

	return strReturn;
}

BOOL KW_OpenAPIContext::IsError(long lErrCode)
{
	CString strMsg = _T("");
	switch (lErrCode)
	{
		////////////////////////////
		// �Ϲ� ��ȸ ���� ó��
	case OP_ERR_SISE_OVERFLOW:		// �ü���ȸ ������
		strMsg = "�ü���ȸ ������";
		break;
	case OP_ERR_RQ_STRUCT_FAIL:		// REQUEST_INPUT_st Failed
		strMsg = "REQUEST_INPUT_st Failed";
		break;
	case OP_ERR_RQ_STRING_FAIL:		// ��û ���� �ۼ� ����
		strMsg = "��û ���� �ۼ� ����";
		break;
	case OP_ERR_NO_DATA:			// �����Ͱ� �������� �ʽ��ϴ�.
		strMsg = "�����Ͱ� �������� �ʽ��ϴ�.";
		break;

		////////////////////////////
		// ���� ���� ��ȸ ���� ó��
	case OP_ERR_OVER_MAX_DATA:			// �ѹ��� ��ȸ ������ ���񰳼��� �ִ� 100���� �Դϴ�.
		strMsg = "�ѹ��� ��ȸ ������ ���񰳼��� �ִ� 100���� �Դϴ�.";
		break;

		////////////////////////////
		// �ֹ� ���� ó��
	case OP_ERR_ORD_WRONG_INPUT:		// �Է°� ����
		strMsg = "�Է°� ����";
		break;
	case OP_ERR_ORD_WRONG_ACCNO:		// ���º�й�ȣ�� �Է��Ͻʽÿ�.
		strMsg = "���º�й�ȣ�� �Է��Ͻʽÿ�.";
		break;
	case OP_ERR_OTHER_ACC_USE:			// Ÿ�ΰ��´� ����� �� �����ϴ�.
		strMsg = "Ÿ�ΰ��´� ����� �� �����ϴ�.";
		break;
	case OP_ERR_MIS_2BILL_EXC:			// �ֹ������� 20����� �ʰ��մϴ�.
		strMsg = "�ֹ������� 20����� �ʰ��մϴ�.";
		break;
	case OP_ERR_MIS_5BILL_EXC:			// �ֹ������� 50����� �ʰ��մϴ�.
		strMsg = "�ֹ������� 50����� �ʰ��մϴ�.";
		break;
	case OP_ERR_MIS_1PER_EXC:			// �ֹ������� �ѹ����ּ��� 1%�� �ʰ��մϴ�.
		strMsg = "�ֹ������� �ѹ����ּ��� 1%�� �ʰ��մϴ�.";
		break;
	case OP_ERR_MIS_3PER_EXC:			// �ֹ������� �ѹ����ּ��� 3%�� �ʰ��� �� �����ϴ�.
		strMsg = "�ֹ������� �ѹ����ּ��� 3%�� �ʰ��� �� �����ϴ�.";
		break;
	case OP_ERR_SEND_FAIL:				// �ֹ����۽���
		strMsg = "�ֹ����ۿ� �����Ͽ����ϴ�..";
		break;
	case OP_ERR_ORD_OVERFLOW:			// �ֹ����� ������
		strMsg = "�ֹ����� ������ �Դϴ�. ��� �� �ٽ� �ֹ��Ͽ� �ּ���.";
		break;
	}

	// ���� �޼��� ó��
	if (!strMsg.IsEmpty())
	{
		AfxMessageBox(strMsg);
		return FALSE;
	}

	return TRUE;
}