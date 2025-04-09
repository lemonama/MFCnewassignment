
// MFCnewDlg.h: 헤더 파일
//

#pragma once
typedef struct
{
	float x;
	float y;
} AT_FPOINT;

// CMFCnewDlg 대화 상자
class CMFCnewDlg : public CDialogEx
{
private:
	CImage m_image;
	BOOL validimgPos(int x, int y);
	// 생성입니다.
public:
	CMFCnewDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCNEW_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


	// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnimage();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	void UpdateDisplay();
	void drawCircle(unsigned char* fm, int i, int j, int nRadius, int nGray);
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	CPoint m_clickPoints[3];
	afx_msg void OnEnChangeEditradi();
	int m_nCircleCount = 0;
	int m_Radius;
	//int m_clickPoints;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnRandom();
	afx_msg void OnBnClickedBtnreeset();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void drawBigCircle(float* r, AT_FPOINT* psRelMatchPos, const AT_FPOINT* psCenterPoint);
	void drawCircleOutline(unsigned char* fm, int x, int y, int m_Radius, int nGray, int thickness);
	afx_msg void OnEnChangeEditBig();
	void DrawRandomCircles();
	void DrawRandom();
	void BigCircle();
	void MoveSCircle();
	int m_Bline;
	BOOL m_isDragging = FALSE;         
	int m_selectedCircleIndex = -1;      
	CPoint m_prevPoint;

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};