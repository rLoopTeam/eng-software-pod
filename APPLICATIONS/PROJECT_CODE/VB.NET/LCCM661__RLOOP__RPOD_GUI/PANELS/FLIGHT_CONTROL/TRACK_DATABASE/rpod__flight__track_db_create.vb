Namespace SIL3.rLoop.rPodControl.Panels.FlightControl.TrackDatabase

    ''' <summary>
    ''' Create the track database files on disk
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Creator
        Inherits LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.PanelTemplate


#Region "DLL"
        ''' <summary>
        ''' The name of our DLL, could be a bit better done with relative paths
        ''' </summary>
        Private Const C_DLL_NAME As String = "..\..\..\PROJECT_CODE\DLLS\LDLL174__RLOOP__LCCM655\bin\Debug\LDLL174__RLOOP__LCCM655.dll"


        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Clear_Array()
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Get_Array(pu8ByteArray() As Byte)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Function u16FCU_FCTL_TRACKDB_WIN32__Get_StructureSize() As UInt16
        End Function
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Array(pu8ByteArray() As Byte)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Header(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Function u16FCTL_TRAKDB_WIN32__ComputeCRC() As UInt16
        End Function
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_CRC(u16Value As UInt16)
        End Sub




        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Accel__Use(u8TrackIndex As Byte, u8Value As Byte)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Accel__Threshold_mm_ss(u8TrackIndex As Byte, s32Thresh_mm_ss As Int32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Accel__Threshold_x10ms(u8TrackIndex As Byte, u32Thresh_x10ms As UInt32)
        End Sub


        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Track__TrackStart_mm(u8TrackIndex As Byte, u32Value As UInt32)
        End Sub

        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Track__TrackEnd_mm(u8TrackIndex As Byte, u32Value As UInt32)
        End Sub

        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Track__TrackLength_mm(u8TrackIndex As Byte, u32Value As UInt32)
        End Sub


        '<System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        'Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_TrackID(u32Value As UInt32)
        'End Sub
        '<System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        'Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_TrackStartXPos(u32Value As UInt32)
        'End Sub
        '<System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        'Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_TrackEndXPos(u32Value As UInt32)
        'End Sub
        '<System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        'Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_LRF_StartXPos(u32Value As UInt32)
        'End Sub
        '<System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        'Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_NumStripes(u32Value As UInt32)
        'End Sub
        '<System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        'Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_StripeStartX(u32Index As UInt32, u32Value As UInt32)
        'End Sub
        '<System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        'Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_EnableAccels(u32Value As UInt32)
        'End Sub
        '<System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        'Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_EnableLRF(u32Value As UInt32)
        'End Sub
        '<System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        'Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_EnableContrast(u32Value As UInt32)
        'End Sub
        '<System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        'Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_HeaderSpare(u32Index As UInt32, u32Value As UInt32)
        'End Sub
        '<System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        'Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Footer(u32Value As UInt32)
        'End Sub

        ''profile system
        '<System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        'Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PusherFrontStartPos(u32Value As UInt32)
        'End Sub
        '<System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        'Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PusherFrontEndPos(u32Value As UInt32)
        'End Sub
        '<System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        'Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PodFrontTargetXPos(u32Value As UInt32)
        'End Sub
        '<System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        'Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Profile_NumSetpoints(u32Value As UInt32)
        'End Sub
        '<System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        'Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Profile_BrakeSetpointPosX(u32Index As UInt32, u32Value As UInt32)
        'End Sub
        '<System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        'Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Profile_BrakeSetpointVelocityX(u32Index As UInt32, u32Value As UInt32)
        'End Sub
        '<System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        'Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Profile_Spare(u32Index As UInt32, u32Value As UInt32)
        'End Sub

#End Region ' #Region "DLL"

#Region "CONSTANTS"

        Private Const C_FCTL_TRACKDB__HEADER_SPARE_WORDS As Integer = 16
        Private Const C_FCTL_TRACKDB__PROFILE_SPARE_WORDS As Integer = 16

        '/** Total number of track databases stored in memory */
        Private Const C_FCTL_TRACKDB__MAX_MEM_DATABASES As Integer = 8

        '/** Max number of stripes the track DB knows about */
        Private Const C_FCTL_TRACKDB__MAX_CONTRAST_STRIPES As Integer = 64


        '/** The maximum number of setpoints */
        Private Const C_FCTL_TRACKDB__MAX_SETPOINTS As Integer = 1024

#End Region '#Region "CONSTANTS"

#Region "MEMBERS"

        Private m_sLogDir As String

        Private m_txtTrackIndex As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U8
        Private m_txtTrackHumanName As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper

        'accel system
        Private m_chkAccel_Use As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.CheckBoxHelper
        Private m_txtAccel_Thresh_mm_ss_s32 As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_S32
        Private m_txtAccel_Timer_x10ms_u32 As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U32
        Private m_txtAccel_Spare_u32 As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U32

        'fwd laser
        Private m_chkFwdLaser_Use As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.CheckBoxHelper
        Private m_txtFwdLaser_Spare0 As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U32
        Private m_txtFwdLaser_Spare1 As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U32
        Private m_txtFwdLaser_Spare2 As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U32

        'contrast laser system
        Private m_chkContLaser_Use As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.CheckBoxHelper
        Private m_txtContLaser_Spare0 As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U32
        Private m_txtContLaser_Spare1 As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U32
        Private m_txtContLaser_Spare2 As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U32


        Private m_txtTrack__Start_mm As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U32
        Private m_txtTrack__End_mm As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U32
        Private m_txtTrack__Length_mm As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U32


        ''' <summary>
        ''' The database directory
        ''' </summary>
        Private m_sDBDir As String

        ''' <summary>
        ''' The CSV to read the track databse system
        ''' </summary>
        Private m_pCSV As LAPP188__RLOOP__LIB.SIL3.FileSupport.CSV

        ''' <summary>
        ''' Choose the database
        ''' </summary>
        Private m_cboDatabase As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ComboBoxHelper

        ''' <summary>
        ''' The current selected index.
        ''' </summary>
        Private m_iCurrentIndex As Integer = -1

#End Region '#Region "MEMBERS"

#Region "NEW"
        ''' <summary>
        ''' New instance
        ''' </summary>
        ''' <param name="sPanelText"></param>
        ''' <remarks></remarks>
        Public Sub New(sPanelText As String, sLog As String)
            MyBase.New(sPanelText)

            Me.m_sLogDir = sLog
            Me.m_sLogDir = Me.m_sLogDir & "TRACK_DB\"

            'check our folder
            LAPP188__RLOOP__LIB.SIL3.FileSupport.FileHelpers.Folder__CheckWarnMake(Me.m_sLogDir)

            Me.m_sDBDir = "..\..\..\..\FIRMWARE\PROJECT_CODE\LCCM655__RLOOP__FCU_CORE\FLIGHT_CONTROLLER\TRACK_DATABASE\DATABASES\"



            'create the log files in prep
            Me.m_pCSV = New LAPP188__RLOOP__LIB.SIL3.FileSupport.CSV(Me.m_sDBDir & "databases2.csv", ",", False, False)
            If Me.m_pCSV.File__Exists = False Then

                If MsgBox("Warn: A new track database CSV will be created, are you sure?", MsgBoxStyle.YesNo) = MsgBoxResult.Yes Then


                    'load up some headers
                    Me.m_pCSV.Header__Add("TRACK_INDEX_U8")

                    Me.m_pCSV.Header__Add("TRACK_HUMAN")


                    'accel subsystem
                    'use the accel system
                    Me.m_pCSV.Header__Add("ACCEL_USE_U8")
                    'The threshold in mm ss
                    Me.m_pCSV.Header__Add("ACCEL_THRESH_MM_SS_S32")
                    'the time the threshold needs to be on 
                    Me.m_pCSV.Header__Add("ACCEL_THRESH_TIME_X10MS_U32")
                    'spare accel
                    Me.m_pCSV.Header__Add("ACCEL_SPARE_U32")


                    'fwd laser
                    'use the fwd laser
                    Me.m_pCSV.Header__Add("FWD_USE_U8")
                    Me.m_pCSV.Header__Add("FWD_SPARE_0_U32")
                    Me.m_pCSV.Header__Add("FWD_SPARE_1_U32")
                    Me.m_pCSV.Header__Add("FWD_SPARE_2_U32")

                    'contrast system
                    'use the contrast laser system
                    Me.m_pCSV.Header__Add("CONT_USE_U8")
                    Me.m_pCSV.Header__Add("CONT_SPARE_0_U32")
                    Me.m_pCSV.Header__Add("CONT_SPARE_1_U32")
                    Me.m_pCSV.Header__Add("CONT_SPARE_2_U32")

                    'pusher
                    Me.m_pCSV.Header__Add("PUSHER_USE_U8")
                    Me.m_pCSV.Header__Add("HOVER_USE_U8")
                    Me.m_pCSV.Header__Add("LGU_USE_U8")
                    Me.m_pCSV.Header__Add("COOLING_USE_U8")

                    'track specifics
                    Me.m_pCSV.Header__Add("TRACK_START_XPOS_MM_U32")
                    Me.m_pCSV.Header__Add("TRACK_END_XPOS_MM_U32")
                    Me.m_pCSV.Header__Add("TRACK_LENGTH_MM_U32")

                    'state machine timers
                    Me.m_pCSV.Header__Add("SM_SPARE0_U32")
                    Me.m_pCSV.Header__Add("SM_SPARE1_U32")
                    Me.m_pCSV.Header__Add("SM_SPARE2_U32")
                    Me.m_pCSV.Header__Add("SM_SPARE3_U32")


                    'braking strategy
                    'control strategy
                    Me.m_pCSV.Header__Add("BRAKE_USE_PID_U8")
                    Me.m_pCSV.Header__Add("BRAKE_TARGET_DISTANCE_F32")

                    'save off the new headers
                    Me.m_pCSV.Header__Save()

                    'read the file.
                    Me.m_pCSV.File__Read()


                    'now add some stuff
                    For iCounter As Integer = 0 To C_FCTL_TRACKDB__MAX_MEM_DATABASES - 1
                        Dim pSB As New System.Text.StringBuilder

                        'index
                        pSB.Append(iCounter.ToString & ",")

                        'human name
                        pSB.Append("NO NAME ASSIGNED" & ",")

                        'ACCEL_USE_U8"
                        pSB.Append("0" & ",")
                        '"ACCEL_THRESH_MM_SS_S32"
                        pSB.Append("0" & ",")
                        '"ACCEL_THRESH_TIME_X10MS_U32"
                        pSB.Append("0" & ",")
                        '"ACCEL_SPARE_U32"
                        pSB.Append("0" & ",")

                        '"FWD_USE_U8"
                        pSB.Append("0" & ",")
                        '"FWD_SPARE_0_U32"
                        pSB.Append("0" & ",")
                        '"FWD_SPARE_1_U32"
                        pSB.Append("0" & ",")
                        '"FWD_SPARE_2_U32"
                        pSB.Append("0" & ",")

                        '"CONT_USE_U8"
                        pSB.Append("0" & ",")
                        '"CONT_SPARE_0_U32"
                        pSB.Append("0" & ",")
                        '"CONT_SPARE_1_U32"
                        pSB.Append("0" & ",")
                        '"CONT_SPARE_2_U32"
                        pSB.Append("0" & ",")


                        'pusher
                        '"PUSHER_USE_U8"
                        pSB.Append("0" & ",")

                        'hover
                        '"HOVER_USE_U8"
                        pSB.Append("0" & ",")

                        'cooling
                        '"COOLING_USE_U8"
                        pSB.Append("0" & ",")

                        'Use the LGU
                        '"LGU_USE_U8"
                        pSB.Append("0" & ",")

                        'track specifics
                        '"TRACK_START_XPOS_MM_U32"
                        pSB.Append("0" & ",")
                        '"TRACK_END_XPOS_MM_U32"
                        pSB.Append("0" & ",")
                        '"TRACK_LENGTH_MM_U32"
                        pSB.Append("0" & ",")

                        '"SM_SPARE0_U32"
                        pSB.Append("0" & ",")
                        '"SM_SPARE1_U32"
                        pSB.Append("0" & ",")
                        '"SM_SPARE2_U32"
                        pSB.Append("0" & ",")
                        '"SM_SPARE3_U32"
                        pSB.Append("0" & ",")

                        '"BRAKE_USE_PID_U8"
                        pSB.Append("0" & ",")
                        '"BRAKE_TARGET_DISTANCE_F32"
                        pSB.Append("0" & ",")

                        Dim sL As String = pSB.ToString
                        sL = sL.Remove(sL.Length - 1, 1)
                        Me.m_pCSV.Write_CSV_Line(sL)


                        ''now write out a list of points to a single file
                        'Dim lStripe As New List(Of String)
                        'For iStripes As Integer = 0 To C_FCTL_TRACKDB__MAX_CONTRAST_STRIPES - 1
                        '    lStripe.Add("0")
                        'Next
                        ''save it off
                        'LAPP188__RLOOP__LIB.SIL3.FileSupport.FileHelpers.File__WriteLines(Me.m_sDBDir & iCounter.ToString("00") & "__stripes.txt", lStripe)

                        ''create the setpoint list
                        'Dim lSet As New List(Of String)
                        'For iSet As Integer = 0 To C_FCTL_TRACKDB__MAX_SETPOINTS - 1
                        '    lSet.Add("0")
                        'Next
                        ''save it off
                        'LAPP188__RLOOP__LIB.SIL3.FileSupport.FileHelpers.File__WriteLines(Me.m_sDBDir & iCounter.ToString("00") & "__set_xpos.txt", lSet)
                        'LAPP188__RLOOP__LIB.SIL3.FileSupport.FileHelpers.File__WriteLines(Me.m_sDBDir & iCounter.ToString("00") & "__set_veloc.txt", lSet)

                    Next 'For iCounter As Integer = 0 To C_FCTL_TRACKDB__MAX_MEM_DATABASES - 1

                End If

            Else

                'read the file
                Me.m_pCSV.File__Read()


            End If


        End Sub
#End Region '#Region "New"

#Region "EVENTS"

        ''' <summary>
        ''' Raised wehen we want to transmit a control packet
        ''' </summary>
        ''' <param name="u16Type"></param>
        ''' <param name="u32Block0"></param>
        ''' <param name="u32Block1"></param>
        ''' <param name="u32Block2"></param>
        ''' <param name="u32Block3"></param>
        ''' <remarks></remarks>

        Public Event UserEvent__SafeUDP__Tx_X4(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, u32Block3 As UInt32)


        ''' <summary>
        ''' New Packet In
        ''' </summary>
        ''' <param name="ePacketType"></param>
        ''' <param name="u16PayloadLength"></param>
        ''' <param name="u8Payload"></param>
        ''' <param name="u16CRC"></param>
        Public Sub InernalEvent__UDPSafe__RxPacketB(ByVal ePacketType As SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T, ByVal u16PayloadLength As LAPP188__RLOOP__LIB.SIL3.Numerical.U16, ByRef u8Payload() As Byte, ByVal u16CRC As LAPP188__RLOOP__LIB.SIL3.Numerical.U16)

            'only do if we have been created
            If MyBase.m_bLayout = True Then

                'check for our sim packet type
                If ePacketType = SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LASER_CONT__TX_LASER_DATA_0 Then


                End If
            End If

        End Sub


#End Region '#Region "EVENTS"

#Region "PANEL LAYOUT"
        ''' <summary>
        ''' Create our layout prior to being shown
        ''' </summary>
        ''' <remarks></remarks>
        Public Overrides Sub LayoutPanel()

            Dim l0 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper(10, 10, "Track Database List", MyBase.m_pInnerPanel)
            Me.m_cboDatabase = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ComboBoxHelper(300, l0)

            'fill
            For iCounter As Integer = 0 To Me.m_pCSV.m_alRows.Count - 1
                Dim pAL As ArrayList = Me.m_pCSV.m_alRows(iCounter)
                Me.m_cboDatabase.Threadsafe__AddItem("INDEX = " & pAL.Item(0).ToString & " [DESC: " & pAL.Item(1).ToString & "]")
            Next
            Me.m_cboDatabase.Threadsafe__SetSelectedIndex(0)

            Dim btnChoose As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Choose", AddressOf Me.btnChooseDB__Click)
            btnChoose.Layout__RightOfControl(Me.m_cboDatabase)

            Dim btnGenBinary As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Gen Binary", AddressOf Me.btnGenBinary__Click)
            btnGenBinary.Layout__RightOfControl(btnChoose)

            Dim btnSave As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Save CSV", AddressOf Me.btnSave__Click)
            btnSave.Layout__RightOfControl(btnGenBinary)


            Dim l1 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Track Index", Me.m_cboDatabase)
            Me.m_txtTrackIndex = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U8(100, l1)
            Me.m_txtTrackIndex.ReadOnly = True

            Dim l1a As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Track Human Name")
            l1a.Layout__AboveRightControl(l1, Me.m_txtTrackIndex)
            Me.m_txtTrackHumanName = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper(300, l1a)


            'accel subsystem
            Dim l100 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Accel mms²", Me.m_txtTrackIndex)
            Me.m_txtAccel_Thresh_mm_ss_s32 = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_S32(100, l100)
            Dim l101 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Accel x10ms")
            l101.Layout__AboveRightControl(l100, Me.m_txtAccel_Thresh_mm_ss_s32)
            Me.m_txtAccel_Timer_x10ms_u32 = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U32(100, l101)
            Dim l102 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Accel Spare")
            l102.Layout__AboveRightControl(l101, Me.m_txtAccel_Timer_x10ms_u32)
            Me.m_txtAccel_Spare_u32 = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U32(100, l102)

            Me.m_chkAccel_Use = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.CheckBoxHelper("Accel: Use", "Accel: Use", "Use Accelerometer System")
            Me.m_chkAccel_Use.Layout__RightOfControl(Me.m_txtAccel_Spare_u32)


            Dim l200 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Fwd: Spare 0", Me.m_txtAccel_Thresh_mm_ss_s32)
            Me.m_txtFwdLaser_Spare0 = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U32(100, l200)
            Dim l201 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Fwd: Spare 1")
            l201.Layout__AboveRightControl(l200, Me.m_txtFwdLaser_Spare0)
            Me.m_txtFwdLaser_Spare1 = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U32(100, l201)
            Dim l202 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Fwd: Spare 2")
            l202.Layout__AboveRightControl(l201, Me.m_txtFwdLaser_Spare1)
            Me.m_txtFwdLaser_Spare2 = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U32(100, l202)
            Me.m_chkFwdLaser_Use = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.CheckBoxHelper("FwdLaser: Use", "FwdLaser: Use", "Use the Fwd Laser")
            Me.m_chkFwdLaser_Use.Layout__RightOfControl(Me.m_txtFwdLaser_Spare2)


            Dim l300 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Cont: Spare 0", Me.m_txtFwdLaser_Spare0)
            Me.m_txtContLaser_Spare0 = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U32(100, l300)
            Dim l301 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Cont: Spare 1")
            l301.Layout__AboveRightControl(l300, Me.m_txtContLaser_Spare0)
            Me.m_txtContLaser_Spare1 = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U32(100, l301)
            Dim l302 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Cont: Spare 2")
            l302.Layout__AboveRightControl(l301, Me.m_txtContLaser_Spare1)
            Me.m_txtContLaser_Spare2 = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U32(100, l302)
            Me.m_chkContLaser_Use = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.CheckBoxHelper("ContLaser: Use", "ContLaser: Use", "Use the Contrast Laser")
            Me.m_chkContLaser_Use.Layout__RightOfControl(Me.m_txtContLaser_Spare2)


            Dim l400 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Track Start mm", Me.m_txtContLaser_Spare0)
            Me.m_txtTrack__Start_mm = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U32(100, l400)
            Dim l401 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Track End mm")
            l401.Layout__AboveRightControl(l400, Me.m_txtTrack__Start_mm)
            Me.m_txtTrack__End_mm = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U32(100, l401)
            Dim l402 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Track Len mm")
            l402.Layout__AboveRightControl(l401, Me.m_txtTrack__End_mm)
            Me.m_txtTrack__Length_mm = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U32(100, l402)


        End Sub

#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON HELPERS"

        ''' <summary>
        ''' Save the current edited page
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnSave__Click(s As Object, e As EventArgs)


            If Me.m_txtTrackHumanName.Dirty = True Then
                Me.m_pCSV.Cell__SetContents("TRACK_HUMAN", Me.m_iCurrentIndex, Me.m_txtTrackHumanName.Text, True)
                Me.m_txtTrackHumanName.Dirty = False
            End If

            If Me.m_chkAccel_Use.Checked = True Then
                Me.m_pCSV.Cell__SetContents("ACCEL_USE_U8", Me.m_iCurrentIndex, "1", True)
            Else
                Me.m_pCSV.Cell__SetContents("ACCEL_USE_U8", Me.m_iCurrentIndex, "0", True)
            End If
            If Me.m_txtAccel_Thresh_mm_ss_s32.Dirty = True Then
                Me.m_pCSV.Cell__SetContents("ACCEL_THRESH_MM_SS_S32", Me.m_iCurrentIndex, Me.m_txtAccel_Thresh_mm_ss_s32.Text.ToString, True)
                Me.m_txtAccel_Thresh_mm_ss_s32.Dirty = False
            End If
            If Me.m_txtAccel_Timer_x10ms_u32.Dirty = True Then
                Me.m_pCSV.Cell__SetContents("ACCEL_THRESH_TIME_X10MS_U32", Me.m_iCurrentIndex, Me.m_txtAccel_Timer_x10ms_u32.Text.ToString, True)
                Me.m_txtAccel_Timer_x10ms_u32.Dirty = False
            End If
            If Me.m_txtAccel_Spare_u32.Dirty = True Then
                Me.m_pCSV.Cell__SetContents("ACCEL_SPARE_U32", Me.m_iCurrentIndex, Me.m_txtAccel_Spare_u32.Text.ToString, True)
                Me.m_txtAccel_Spare_u32.Dirty = False
            End If


            If Me.m_chkFwdLaser_Use.Checked = True Then
                Me.m_pCSV.Cell__SetContents("FWD_USE_U8", Me.m_iCurrentIndex, "1", True)
            Else
                Me.m_pCSV.Cell__SetContents("FWD_USE_U8", Me.m_iCurrentIndex, "0", True)
            End If
            If Me.m_txtFwdLaser_Spare0.Dirty = True Then
                Me.m_pCSV.Cell__SetContents("FWD_SPARE_0_U32", Me.m_iCurrentIndex, Me.m_txtFwdLaser_Spare0.Text.ToString, True)
                Me.m_txtFwdLaser_Spare0.Dirty = False
            End If
            If Me.m_txtFwdLaser_Spare1.Dirty = True Then
                Me.m_pCSV.Cell__SetContents("FWD_SPARE_1_U32", Me.m_iCurrentIndex, Me.m_txtFwdLaser_Spare1.Text.ToString, True)
                Me.m_txtFwdLaser_Spare1.Dirty = False
            End If
            If Me.m_txtFwdLaser_Spare2.Dirty = True Then
                Me.m_pCSV.Cell__SetContents("FWD_SPARE_2_U32", Me.m_iCurrentIndex, Me.m_txtFwdLaser_Spare2.Text.ToString, True)
                Me.m_txtFwdLaser_Spare2.Dirty = False
            End If



            If Me.m_chkContLaser_Use.Checked = True Then
                Me.m_pCSV.Cell__SetContents("CONT_USE_U8", Me.m_iCurrentIndex, "1", True)
            Else
                Me.m_pCSV.Cell__SetContents("CONT_USE_U8", Me.m_iCurrentIndex, "0", True)
            End If
            If Me.m_txtContLaser_Spare0.Dirty = True Then
                Me.m_pCSV.Cell__SetContents("CONT_SPARE_0_U32", Me.m_iCurrentIndex, Me.m_txtContLaser_Spare0.Text.ToString, True)
                Me.m_txtContLaser_Spare0.Dirty = False
            End If
            If Me.m_txtContLaser_Spare1.Dirty = True Then
                Me.m_pCSV.Cell__SetContents("CONT_SPARE_1_U32", Me.m_iCurrentIndex, Me.m_txtContLaser_Spare1.Text.ToString, True)
                Me.m_txtContLaser_Spare1.Dirty = False
            End If
            If Me.m_txtContLaser_Spare2.Dirty = True Then
                Me.m_pCSV.Cell__SetContents("CONT_SPARE_2_U32", Me.m_iCurrentIndex, Me.m_txtContLaser_Spare2.Text.ToString, True)
                Me.m_txtContLaser_Spare2.Dirty = False
            End If


            'track specifics
            If Me.m_txtTrack__Start_mm.Dirty = True Then
                Me.m_pCSV.Cell__SetContents("TRACK_START_XPOS_MM_U32", Me.m_iCurrentIndex, Me.m_txtTrack__Start_mm.Text.ToString, True)
                Me.m_txtTrack__Start_mm.Dirty = False
            End If
            If Me.m_txtTrack__End_mm.Dirty = True Then
                Me.m_pCSV.Cell__SetContents("TRACK_END_XPOS_MM_U32", Me.m_iCurrentIndex, Me.m_txtTrack__End_mm.Text.ToString, True)
                Me.m_txtTrack__End_mm.Dirty = False
            End If
            If Me.m_txtTrack__Length_mm.Dirty = True Then
                Me.m_pCSV.Cell__SetContents("TRACK_LENGTH_MM_U32", Me.m_iCurrentIndex, Me.m_txtTrack__Length_mm.Text.ToString, True)
                Me.m_txtTrack__Length_mm.Dirty = False
            End If


        End Sub

        ''' <summary>
        ''' Choose the database
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnChooseDB__Click(s As Object, e As EventArgs)

            'assign the current index.
            Me.m_iCurrentIndex = Me.m_cboDatabase.SelectedIndex

            'see if the points file exists
            Dim iItem As Integer = 0
            Me.m_txtTrackIndex.Threadsafe__SetText(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(iItem).ToString)
            iItem += 1

            Me.m_txtTrackHumanName.Threadsafe__SetText(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(iItem).ToString)
            iItem += 1

            'use accel
            If Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(iItem).ToString = "1" Then
                Me.m_chkAccel_Use.Checked = True
            Else
                Me.m_chkAccel_Use.Checked = False
            End If
            iItem += 1
            Me.m_txtAccel_Thresh_mm_ss_s32.Threadsafe__SetText(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(iItem).ToString)
            iItem += 1
            Me.m_txtAccel_Timer_x10ms_u32.Threadsafe__SetText(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(iItem).ToString)
            iItem += 1
            Me.m_txtAccel_Spare_u32.Threadsafe__SetText(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(iItem).ToString)
            iItem += 1

            'fwd laser
            If Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(iItem).ToString = "1" Then
                Me.m_chkFwdLaser_Use.Checked = True
            Else
                Me.m_chkFwdLaser_Use.Checked = False
            End If
            iItem += 1
            Me.m_txtFwdLaser_Spare0.Threadsafe__SetText(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(iItem).ToString)
            iItem += 1
            Me.m_txtFwdLaser_Spare1.Threadsafe__SetText(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(iItem).ToString)
            iItem += 1
            Me.m_txtFwdLaser_Spare2.Threadsafe__SetText(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(iItem).ToString)
            iItem += 1

            'contrast laser
            If Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(iItem).ToString = "1" Then
                Me.m_chkContLaser_Use.Checked = True
            Else
                Me.m_chkContLaser_Use.Checked = False
            End If
            iItem += 1
            Me.m_txtContLaser_Spare0.Threadsafe__SetText(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(iItem).ToString)
            iItem += 1
            Me.m_txtContLaser_Spare0.Threadsafe__SetText(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(iItem).ToString)
            iItem += 1
            Me.m_txtContLaser_Spare0.Threadsafe__SetText(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(iItem).ToString)
            iItem += 1


            'push, hover, cooling, lgu
            iItem += 1
            iItem += 1
            iItem += 1
            iItem += 1

            Me.m_txtTrack__Start_mm.Threadsafe__SetText(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(iItem).ToString)
            iItem += 1
            Me.m_txtTrack__End_mm.Threadsafe__SetText(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(iItem).ToString)
            iItem += 1
            Me.m_txtTrack__Length_mm.Threadsafe__SetText(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(iItem).ToString)
            iItem += 1



        End Sub

        ''' <summary>
        ''' Generate the binary file
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnGenBinary__Click(s As Object, e As EventArgs)

            Me.Database__GenBinary()
        End Sub

#End Region '#Region "BUTTON HELPERS"

#Region "LOAD DATABASE"

        ''' <summary>
        ''' Load the track database files in text format
        ''' </summary>
        ''' <param name="iIndex"></param>
        Private Sub Database__LoadText(iIndex As Integer)



        End Sub

        ''' <summary>
        ''' Generate the binary form of the database file
        ''' </summary>
        Private Sub Database__GenBinary()


            'clear the internal mem array
            vFCU_FCTL_TRACKDB_WIN32__Clear_Array()

            'setup the header
            vFCU_FCTL_TRACKDB_WIN32__Set_Header(&HABCD1234L)

            'setup the accel
            For iRow As Integer = 0 To Me.m_pCSV.m_alRows.Count - 1
                Dim iItem As Integer = 0

                'track ID
                iItem += 1

                'human nam
                iItem += 1

                Dim u8Row As Byte = CByte(iRow)
                Dim u8Temp As Byte

                u8Temp = CByte(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(iItem).ToString)
                vFCU_FCTL_TRACKDB_WIN32__Set_Accel__Use(u8Row, u8Temp)
                iItem += 1

                Dim s32Temp As Int32 = CInt(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(iItem).ToString)
                vFCU_FCTL_TRACKDB_WIN32__Set_Accel__Threshold_mm_ss(u8Row, s32Temp)
                iItem += 1

                Dim u32Temp As UInt32 = CUInt(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(iItem).ToString)
                vFCU_FCTL_TRACKDB_WIN32__Set_Accel__Threshold_x10ms(u8Row, u32Temp)
                iItem += 1
                'spare
                iItem += 1

                'fwd laser
                iItem += 1
                iItem += 1
                iItem += 1
                iItem += 1

                'contrast laser
                iItem += 1
                iItem += 1
                iItem += 1
                iItem += 1

                'push, hover, cooling, lgu
                iItem += 1
                iItem += 1
                iItem += 1
                iItem += 1

                'track specifics
                vFCU_FCTL_TRACKDB_WIN32__Set_Track__TrackStart_mm(iRow, CUInt(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(iItem).ToString))
                iItem += 1
                vFCU_FCTL_TRACKDB_WIN32__Set_Track__TrackEnd_mm(iRow, CUInt(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(iItem).ToString))
                iItem += 1
                vFCU_FCTL_TRACKDB_WIN32__Set_Track__TrackLength_mm(iRow, CUInt(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(iItem).ToString))
                iItem += 1


            Next

            'finally compute the CRC
            Dim u16CRC As UInt16 = u16FCTL_TRAKDB_WIN32__ComputeCRC()
            vFCU_FCTL_TRACKDB_WIN32__Set_CRC(u16CRC)


            'do the save
            Dim u8Array() As Byte
            Dim u16Size As UInt16 = u16FCU_FCTL_TRACKDB_WIN32__Get_StructureSize()
            ReDim u8Array(u16Size - 1)

            Dim pS As New System.IO.FileStream(Me.m_sDBDir & "database2.bin", IO.FileMode.Create)
            Dim pW As New System.IO.BinaryWriter(pS)

            'load
            vFCU_FCTL_TRACKDB_WIN32__Get_Array(u8Array)

            'file it
            pW.Write(u8Array, 0, u16Size)

            'close off
            pW.Close()
            pS.Close()

            MsgBox("File Saved...")

        End Sub

#End Region '#Region "LOAD DATABASE"

    End Class


End Namespace
