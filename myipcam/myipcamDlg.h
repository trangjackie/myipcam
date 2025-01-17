
// myipcamDlg.h : header file	
//

#pragma once

#include <list>
#include"HOEM_IPCam_SDK.h"
#include"HOEM_Play_SDK.h"
#include"HIPCam_Error.h"
#include"HPlay_Error.h"
#include"AVISave.h"

#include <math.h>
#include <time.h>
#include <io.h>
#include <stdio.h>
#include <wchar.h>
#include "stdafx.h"

#include "cv.h"
#include "highgui.h"

// CmyipcamDlg dialog
class CmyipcamDlg : public CDialogEx
{
// Construction
public:
	CmyipcamDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYIPCAM_DIALOG };
#endif
	// for IP camera control
	CEdit	m_Port;
	CEdit	m_Pass;
	CEdit	m_User;
	CEdit	m_IP;
	CStatic	m_s;					// display video and image
	CButton m_button_conn;
	CButton m_button_ptz_home;
	CButton m_button_ptz_left;
	CButton m_button_ptz_right;
	CButton m_button_ptz_up;
	CButton m_button_ptz_down;
	CButton m_button_ptz_zoomin;
	CButton m_button_ptz_zoomout;
	CButton m_button_ptz_focusin;
	CButton m_button_ptz_focusout;
	CStatic m_label_ip;
	CStatic m_label_port;
	CStatic m_label_user;
	CStatic m_label_pw;



	// for results display
	CEdit	m_CS_serial;
	CEdit	m_CS_Tam_num;
	CEdit	m_CS_Tam_text;
	CEdit	m_CS_Huong_num;
	CEdit	m_CS_Huong_text;
	CEdit	m_CS_HCDN_num;
	CEdit	m_CS_HCDN_text;
	CEdit	m_CS_HCB_num;
	CEdit	m_CS_HCB_text;

	CListCtrl m_CS_list_result;
	// for main control
	CButton m_CS_start;
	CButton m_CS_evaluate;
	CButton m_CS_save;
	CButton m_CS_stop;

	// for configuration setup
	CButton m_button_config;
	CEdit	m_License;
	CEdit	m_CS_Shoot_number;
	CEdit	m_CS_Center_x;
	CEdit	m_CS_Center_y;
	CEdit	m_CS_Width_mm;
	CEdit	m_CS_Width_pix;
	CEdit	m_CS_Peri_pix;
	CComboBox m_CS_Gun_type;
	CButton m_button_target_clear;
	CButton m_button_cs_center;
#ifdef VERSION_2

#elif VERSION_1
	CButton m_button_cs_width;
	CButton m_button_cs_peri;
#endif // VERSION_2
	CButton m_button_cfg_save;
	CButton m_button_cfg_cancel;
	CStatic m_label_code;
	CStatic m_label_guntype;
	CStatic m_label_shoot;
	CStatic m_label_centerx;
	CStatic m_label_centery;
	CStatic m_label_widthmm;
	CStatic m_label_widthpix;
	CStatic m_label_peripix;
	CStatic m_config_group;

	CStatic m_CurrentTime;
	


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	// for camera
	HBRUSH m_Color;

	HWND m_HWND_video;
	RECT m_Rect_video;
	HWND m_HWND_opencv;


	//HFrame *m_PlayBackFrameList[200];
	
	HANDLE m_hCam;
	static int CALLBACK EventCallback(int iContext, HANDLE hCam, unsigned char ucChannel, int iEventNum);
	int m_Status;
	static int CALLBACK FrameCallback(int iContext, unsigned char ucChannel, HFrame *pFrame, HVideo_Info VInfo);
	AVIFileSave m_AVISaver;

	int m_iPlayBackCount;
	bool m_bRecordPlayBack;

	std::list<HFrame*> m_FrameList;
	bool m_bPushList;
	int m_ICount;
	int m_lWidth;
	int m_lHeight;

	// method for generate active code 
	DWORD ActiveCode(DWORD serialOfC);
	DWORD GetSerialDiskC();

	// method for HCS
	int captureImage_C();
	int captureImage(std::string strName, int scType, IplImage **img);
	int readConfig();
	int saveConfig();
	void showConfig();
	int addGunList();
	static void Interact_opencv(int event, int x, int y, int flags, void* param);
	int Ketqua_Exe();
	int Detect_LT_Exe();
	int detectCenter(int xm1, int ym1, int xm2, int ym2, float zoom, IplImage *img 
#ifdef VERSION_2
	, int *width, int *cv
#endif // VERSION_2
	);
	int conCenterPoint(CvSeq *mlgc, CvPoint *cvP);
	int conCenterPointAndWidth(CvSeq *mlgc, CvPoint *cvP, int *width);
	int cs_preProcess(IplImage *img_color, IplImage **img_gray, IplImage **img_bw);
	int cs_resFind();
	int cs_conFindBia(IplImage *img, CvSeq **mlgc);
	int cs_conFindVD(IplImage *img, CvSeq *mlgc[]);
	int cs_resView();
	void Set_BKDoTrung();
	int cs_VeVetDanCu(IplImage **img);
	float cs_tinhDoLechTamMM(CvPoint TDan, CvPoint TBia);
	float cs_tinhDoLechHngMM(CvPoint TDan, CvPoint TBia);
	float cs_tinhDoLechTamHC(float tam);
	float cs_tinhDoLechHngHC(float huong);
	void saveResults();

	// variable for HCS
	IplImage *img_first;			// Ảnh đầu tiên khi bắt đầu loạt bắn 
	IplImage *img_first_gray;
	IplImage *img_first_bw;			// Ảnh ngưỡng của anh đầu tiên
	IplImage *img_evaluate;			// Ảnh khi đánh giá
	IplImage *img_evaluate_gray;
	IplImage *img_evaluate_bw;
	IplImage *img_evaluate_final;			// Ảnh đánh giá cuối cùng
	IplImage *img_centerDetect;
	IplImage *img_widthDetect;
	IplImage *img_contourDetect;
	IplImage *img_temp;
	IplImage *imgC;
	IplImage *img_video_test;

	int cs_saiso;
	DWORD cs_active_code;
	DWORD cs_seed_code;
	int cs_TV10_LechX = 0;			// Do lech cua tam vong muoi so voi TRUNG DIEM cua bia theo chieu X, don vi la Pixel
	int cs_TV10_LechY = 0;			// Do lech cua tam vong muoi so voi TRUNG DIEM cua bia theo chieu Y, don vi la Pixel
	int cs_DoRongBia_mm = 500;			// Do rong cua bia tinh bang milimet
	int cs_DoRongBia_ps = 0;			// Do rong cua bia tinh bang pixels
	int cs_ContourLen = 1000;			// Do dai Bien
	int cs_SoPhatBan = 3;			// So phat ban
	int cs_ThoiGian = 0;				// Thoi gian 1 lan chinh sung
	int cs_LoaiSung = 1;				// Loai sung: 1-AK, 2-K54....
	int cs_IntevalTime = 40;		// Thời gian đồng hồ nhịp
	WCHAR cs_FileName[MAX_FILE_PATH];
	int cs_scType = 3;				// 1 - Video File, 2 - Video Card, 3 - Images
	float cs_CoDan = 1;				// Cỡ đạn
	int cs_BanKinh;
	int cs_ContourLenRange = 150;
	float HesoZoom = 1;
	int i_img_video_test_count = 1;
	int cs_con_len_max = 670;		// Do dai toi da BIEN
	int cs_con_len_min = 600;		// Do dai toi thieu BIEN

	int cs_SoPhatBanThuc = 0;		// So phat ban thuc
	CvSeq* cs_contourBia0 = NULL;		// Contour cua bia chuan.
	CvSeq* cs_contourBia1 = NULL;		// Contour cua bia khi đánh giá.
	CvSeq *cs_contourVD[MAX_SO_VIEN_DAN];			// Contour vết đạn

	CvPoint cs_TV10, cs_TVDN;			// Toa do anh cua TAM VONG 10 va TAM VET DAN
	CvPoint cs_TVDNN[MAX_SO_VIEN_DAN];
	CvPoint cs_TVD[1000];					// Vết đạt cũ
	int cs_SoVetDan = 0;					// Biến lưu số vết đạt
	int cs_SoLoatBan = 0;					// Biến lưu số loạt bắn
	int cs_nguong_128 = 128;				// Nguong 128
	int cs_nguong_255 = 255;				// Nguong 255
	int cs_codan_max = 50;					// Co dan max
	int cs_codan_min = 8;					// Co dan min
	float cs_radius;
	int cs_BKDoTrung[19];
	// Khai bao xu ly mouse
	int cmd = DETECT_NN;
	int msd = 0;
	CvPoint XT;
	int xm1 = 0, ym1 = 0, xm2 = 0, ym2 = 0;
	int cs_mode = -1;					// for function mode: 0-evaluation mode, 1-center detection, 2-width detect, 3-peri detect	


	// methods for GUI
	void enableConfigGUI(int enable);
	void setupListResult();
	void insertListResult(int *index, CString sosung, int sodan, CString lechtam, CString lechhuong, float dochum);
	void stateProgram(int state);
	void DisplayIplImageToPictureBox(IplImage* pImgIpl, CDC* pDC, CRect rect);
	void myShowImage(IplImage* img);
	int iState = STATE_START_READY;

public:
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonPtzUp();
	afx_msg void OnBnClickedButtonPtzLeft();
	afx_msg void OnBnClickedButtonPtzDown();
	afx_msg void OnBnClickedButtonPtzHome();
	afx_msg void OnBnClickedButtonPtzRight();
	afx_msg void OnBnClickedButtonPtzZo();
	afx_msg void OnBnClickedButtonPtzZi();
	afx_msg void OnBnClickedButtonPtzFp();
	afx_msg void OnBnClickedButtonPtzFn();
	afx_msg void OnBnClickedButtonCsEvaluation();
	afx_msg void OnBnClickedButtonCsStart();
	afx_msg void OnBnClickedButtonCsCfgCancel();
	afx_msg void OnBnClickedButtonCsCfgSave();
#ifdef VERSION_2

#elif VERSION_1
	afx_msg void OnBnClickedButtonCsWidth();
#endif // VERSION_2
	
	afx_msg void OnBnClickedButtonConfig();
	afx_msg void OnBnClickedButtonCsCenter();
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnCbnSelchangeComboGunType();
	afx_msg void OnEnChangeEditShootNumber();
	afx_msg void OnBnClickedButtonCsSave();
	afx_msg void OnBnClickedButtonCsStop();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonCsTagetClear();
};
