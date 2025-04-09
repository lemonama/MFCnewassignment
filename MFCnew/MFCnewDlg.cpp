
// MFCnewDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCnew.h"
#include "MFCnewDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include "Process.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CMFCnewDlg 대화 상자



CMFCnewDlg::CMFCnewDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCNEW_DIALOG, pParent)

	, m_Radius(10)
	, m_nCircleCount(0)
	, m_Bline(3)
{
	//for (int i = 0; i < 3; i++)
	//{
	//	m_clickPoints[i] = CPoint(0, 0);
	//}
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCnewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_radi, m_Radius);

	DDX_Text(pDX, IDC_EDIT_Big, m_Bline);
}

BEGIN_MESSAGE_MAP(CMFCnewDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Btn_image, &CMFCnewDlg::OnBnClickedBtnimage)
	ON_BN_CLICKED(IDOK, &CMFCnewDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCnewDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT_radi, &CMFCnewDlg::OnEnChangeEditradi)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_Btn_Random, &CMFCnewDlg::OnBnClickedBtnRandom)
	ON_BN_CLICKED(IDC_Btn_reeset, &CMFCnewDlg::OnBnClickedBtnreeset)
	ON_EN_CHANGE(IDC_EDIT_Big, &CMFCnewDlg::OnEnChangeEditBig)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CMFCnewDlg 메시지 처리기

BOOL CMFCnewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	srand((unsigned int)time(NULL));
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCnewDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCnewDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCnewDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCnewDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void CMFCnewDlg::OnBnClickedBtnimage()
{
	CRect rect;
	GetClientRect(&rect);

	int nWidth = rect.Width();
	int nHeight = rect.Height();
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}
	//CClientDC dc(this);
	//m_image.Draw(dc, 0, 0);
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);
	UpdateDisplay();
}

void CMFCnewDlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 40);
}

void CMFCnewDlg::OnEnChangeEditradi()
{
	UpdateData(TRUE);
}

void CMFCnewDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_image.IsNull())
		return;
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	CPoint mousePoint = point;

	for (int i = 0; i < m_nCircleCount; i++)
	{
		int dx = point.x - m_clickPoints[i].x;
		int dy = point.y - m_clickPoints[i].y;
		if (sqrt(dx * dx + dy * dy) <= m_Radius) // 작은 원 안인지 측정
		{
			m_selectedCircleIndex = i; // 몇 번째 원 선택했는지 기억
			m_isDragging = TRUE;
			m_prevPoint = point; // 좌표 저장
			return;
		}
	}

	if (m_nCircleCount < 3)
	{
		// 작은 원 찍기
		drawCircle(fm, mousePoint.x - 10, mousePoint.y - 50, m_Radius, 0);
		m_clickPoints[m_nCircleCount] = mousePoint;
		m_nCircleCount++;
		cout << mousePoint.x << "." << mousePoint.y << endl;
		UpdateDisplay();
	}
	if (m_nCircleCount == 3)
	{
		BigCircle(); //큰원 만들기
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CMFCnewDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_isDragging && m_selectedCircleIndex != -1)
	{
		// 움직인 만큼 원 위치 업데이트
		int dx = point.x - m_prevPoint.x;
		int dy = point.y - m_prevPoint.y;
		m_clickPoints[m_selectedCircleIndex].x += dx;
		m_clickPoints[m_selectedCircleIndex].y += dy;
		m_prevPoint = point;

		// 그림 새로 업데이트
		
		MoveSCircle();
		BigCircle();
		UpdateDisplay();// 큰 원도 다시 그려
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

void CMFCnewDlg::MoveSCircle()
{
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	memset(fm, 255, m_image.GetPitch() * m_image.GetHeight());

	for (int i = 0; i < m_nCircleCount; i++)
	{
		drawCircle(fm, m_clickPoints[i].x - 10, m_clickPoints[i].y - 50, m_Radius, 0);
	}

	Invalidate(FALSE); // 화면 다시 그리기 요청
	UpdateWindow();
}

void CMFCnewDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_isDragging = FALSE;
	m_selectedCircleIndex = -1;

	CDialogEx::OnLButtonUp(nFlags, point);
}
void CMFCnewDlg::BigCircle()
{
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	if (m_nCircleCount == 3)
	{
		// 세 점을 지나는 큰 원 그리기
		AT_FPOINT clickPointsF[3];
		for (int i = 0; i < 3; ++i)
		{
			clickPointsF[i].x = (float)m_clickPoints[i].x;
			clickPointsF[i].y = (float)m_clickPoints[i].y - 40;
		}
		float area = 0.5f * fabs(clickPointsF[0].x * (clickPointsF[1].y - clickPointsF[2].y) +
			clickPointsF[1].x * (clickPointsF[2].y - clickPointsF[0].y) +
			clickPointsF[2].x * (clickPointsF[0].y - clickPointsF[1].y));

		if (area == 0)
		{
			throw std::runtime_error("세 점이 일직선이라 터집니다.");
		}
		AT_FPOINT center;
		float radius;

		drawBigCircle(&radius, &center, clickPointsF);

		// 계산한 중심과 반지름으로 큰 원 그리기
		drawCircleOutline(fm, (int)(center.x - radius), (int)(center.y - radius), (int)radius, 0, m_Bline);

		UpdateDisplay();
	}
}

void CMFCnewDlg::OnBnClickedBtnRandom()
{
	std::thread drawThread(&CMFCnewDlg::DrawRandomCircles, this);
	drawThread.detach(); // 메인 스레드랑 분리 (detach)
}

void CMFCnewDlg::DrawRandomCircles()
{
	for (int i = 0; i < 10; ++i)
	{
		if (m_nCircleCount == 0)
			return;

		DrawRandom(); // 한번 그리는 함수 따로 뺄게
		std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 0.5초 대기
	}
}

void CMFCnewDlg::DrawRandom()
{
	//렌덤으로 원 그릴시 작은 원의 drawCircle 좌표가 살짝 뒤틀리는거 같습니다 원래 원이 있어야할 위치의 좌표에 클릭하면 드래그 가능합니다
	if (m_nCircleCount == 0)
		return;

	unsigned char* fm = (unsigned char*)m_image.GetBits();
	memset(fm, 255, m_image.GetPitch() * m_image.GetHeight());

	int imgWidth = m_image.GetWidth();
	int imgHeight = m_image.GetHeight();

	//CRect rect(0, 30, imgWidth, imgHeight);
	//CRect rt[4];
	//for (int k = 0; k < 4; k++) {
	//	rt[k] = rect;
	//	int offsetX = (k % 2) * (imgWidth / 2);
	//	int offsetY = (k / 2) * (imgHeight / 2);
	//	rt[k].OffsetRect(offsetX, offsetY);
	//}

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	srand(seed); // seed 매번 다르게

	for (int i = 0; i < m_nCircleCount; i++)
	{
		int x = (rand() % (imgWidth - 2 * m_Radius)) + m_Radius;
		int y = (rand() % (imgHeight - 2 * m_Radius)) + m_Radius;

		m_clickPoints[i] = CPoint(x + 10, y + 50);// y 40 시작 화면 반영

		drawCircle(fm, x, y, m_Radius, 0 + (i * 70)); //몇번째 원인지 알기위해서 색깔 변화
	}
	if (m_nCircleCount == 3)
	{
		BigCircle();
	}

	UpdateDisplay();
}

void CMFCnewDlg::OnBnClickedBtnreeset()
{
	if (m_image.IsNull())
		return;

	unsigned char* fm = (unsigned char*)m_image.GetBits();
	memset(fm, 255, m_image.GetPitch() * m_image.GetHeight()); // 전체 흰색으로 초기화

	m_nCircleCount = 0; //  원 카운트 초기화
	// memset(m_clickPoints, 0, sizeof(m_clickPoints));

	UpdateDisplay();
}
void CMFCnewDlg::drawBigCircle(float* r, AT_FPOINT* psRelMatchPos, const AT_FPOINT* psCenterPoint)
{
	// Point 구조체로 좌표 받아오기 후 각 점의 좌표를 이용하여 원의 중심과 반지름을 계산
	const AT_FPOINT& p0 = psCenterPoint[0];
	const AT_FPOINT& p1 = psCenterPoint[1];
	const AT_FPOINT& p2 = psCenterPoint[2];

	AT_FPOINT mid1, mid2;
	mid1.x = 0.5f * (p0.x + p1.x);
	mid1.y = 0.5f * (p0.y + p1.y);
	mid2.x = 0.5f * (p0.x + p2.x);
	mid2.y = 0.5f * (p0.y + p2.y);

	double a1 = -1.0 * (p0.x - p1.x) / (p0.y - p1.y);
	double b1 = mid1.y - a1 * mid1.x;
	double a2 = -1.0 * (p0.x - p2.x) / (p0.y - p2.y);
	double b2 = mid2.y - a2 * mid2.x;

	if (a1 == a2)
		return;

	double cx = (b2 - b1) / (a1 - a2);
	double cy = a1 * cx + b1;

	psRelMatchPos->x = static_cast<float>(cx);
	psRelMatchPos->y = static_cast<float>(cy);

	*r = sqrtf(powf(p0.x - psRelMatchPos->x, 2) + powf(p0.y - psRelMatchPos->y, 2));//반지름 계산
}

BOOL CMFCnewDlg::validimgPos(int x, int y)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	CRect rect(0, 0, nWidth, nHeight);

	return rect.PtInRect(CPoint(x, y));
}

void CMFCnewDlg::drawCircle(unsigned char* fm, int x, int y, int m_Radius, int nGray)
{
	int nCenterX = x + m_Radius;
	int nCenterY = y + m_Radius;
	int nPitch = m_image.GetPitch();

	for (int j = y; j < y + m_Radius * 2; j++) {
		for (int i = x; i < x + m_Radius * 2; i++) {
			if (isInCircle(i, j, nCenterX, nCenterY, m_Radius))
				if (validimgPos(i, j))
					fm[j * nPitch + i] = (unsigned char)nGray;
		}
	}
}

bool CMFCnewDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int m_Radius)
{
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < m_Radius * m_Radius) {
		bRet = true;
	}

	return bRet;
}

void CMFCnewDlg::drawCircleOutline(unsigned char* fm, int x, int y, int m_Radius, int nGray, int thickness)
{
	int nCenterX = x + m_Radius;
	int nCenterY = y + m_Radius;
	int nPitch = m_image.GetPitch();

	for (int j = y; j < y + m_Radius * 2; j++) {
		for (int i = x; i < x + m_Radius * 2; i++) {
			if (!validimgPos(i, j))
				continue;

			// 중심에서 현재 점까지 거리 계산
			float dist = sqrtf((i - nCenterX) * (i - nCenterX) + (j - nCenterY) * (j - nCenterY));

			// 반지름과의 차이를 기준으로 테두리 안에 있으면 찍는다
			if (dist >= m_Radius - thickness / 2.0f && dist <= m_Radius + thickness / 2.0f)
				fm[j * nPitch + i] = (unsigned char)nGray;
		}
	}
}

void CMFCnewDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}

void CMFCnewDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void CMFCnewDlg::OnEnChangeEditBig()
{
	UpdateData(TRUE);
}

