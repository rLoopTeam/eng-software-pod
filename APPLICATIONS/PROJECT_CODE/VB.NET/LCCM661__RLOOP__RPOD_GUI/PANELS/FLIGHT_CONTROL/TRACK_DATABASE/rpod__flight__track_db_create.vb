Namespace SIL3.rLoop.rPodControl.Panels.FlightControl.TrackDatabase

    ''' <summary>
    ''' Create the track database files on disk
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Creator
        Inherits SIL3.ApplicationSupport.PanelTemplate


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
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_DataLength(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_TrackID(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_TrackStartXPos(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_TrackEndXPos(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_LRF_StartXPos(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_NumStripes(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_StripeStartX(u32Index As UInt32, u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_HeaderSpare(u32Index As UInt32, u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Footer(u32Value As UInt32)
        End Sub

        'profile system
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PusherFrontStartPos(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PusherFrontEndPos(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PodFrontTargetXPos(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Profile_NumSetpoints(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Profile_BrakeSetpointPosX(u32Index As UInt32, u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Profile_BrakeSetpointVelocityX(u32Index As UInt32, u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Profile_Spare(u32Index As UInt32, u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Function u16FCTL_TRAKDB_WIN32__ComputeCRC() As UInt16
        End Function
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_CRC(u16Value As UInt16)
        End Sub

#End Region ' #Region "DLL"

#Region "CONSTANTS"

        Private Const C_FCTL_TRACKDB__HEADER_SPARE_WORDS As Integer = 16 + 4

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

        ''' <summary>
        ''' The database directory
        ''' </summary>
        Private m_sDBDir As String

        ''' <summary>
        ''' The CSV to read the track databse system
        ''' </summary>
        Private m_pCSV As SIL3.FileSupport.CSV

        ''' <summary>
        ''' Choose the database
        ''' </summary>
        Private m_cboDatabase As SIL3.ApplicationSupport.ComboBoxHelper

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
            SIL3.FileSupport.FileHelpers.Folder__CheckWarnMake(Me.m_sLogDir)

            Me.m_sDBDir = "D:\LOCKIE\DESIGN\RLOOP\FIRMWARE\PROJECT_CODE\LCCM655__RLOOP__FCU_CORE\FLIGHT_CONTROLLER\TRACK_DATABASE\DATABASES\"

            'create the log files in prep
            Me.m_pCSV = New SIL3.FileSupport.CSV(Me.m_sDBDir & "databases.csv", ",", False, False)
            If Me.m_pCSV.File__Exists = False Then

                If MsgBox("Warn: A new track database CSV will be created, are you sure?", MsgBoxStyle.YesNo) = MsgBoxResult.Yes Then


                    'load up some headers
                    Me.m_pCSV.Header__Add("TRACK_INDEX")
                    Me.m_pCSV.Header__Add("TRACK_HUMAN_NAME")
                    Me.m_pCSV.Header__Add("LAST_EDIT_TIME")

                    Me.m_pCSV.Header__Add("TRACK_START_XPOS_MM")
                    Me.m_pCSV.Header__Add("TRACK_END_XPOS_MM")
                    Me.m_pCSV.Header__Add("LRF_START_POS_MM")
                    Me.m_pCSV.Header__Add("NUM_STRIPES")

                    For iCounter As Integer = 0 To C_FCTL_TRACKDB__HEADER_SPARE_WORDS - 1
                        Me.m_pCSV.Header__Add("SPARE_" & iCounter.ToString("00"))
                    Next

                    'save off the new headers
                    Me.m_pCSV.Header__Save()

                    'read the file.
                    Me.m_pCSV.File__Read()


                    'now add some stuff
                    For iCounter As Integer = 0 To C_FCTL_TRACKDB__MAX_MEM_DATABASES - 1
                        Dim pSB As New System.Text.StringBuilder

                        'index
                        pSB.Append(iCounter.ToString & ",")
                        pSB.Append("N/A" & ",")
                        pSB.Append(Now.ToString.Replace(",", "_") & ",")

                        pSB.Append("0" & ",")
                        pSB.Append("0" & ",")
                        pSB.Append("0" & ",")
                        pSB.Append("0" & ",")

                        For iCounter2 As Integer = 0 To C_FCTL_TRACKDB__HEADER_SPARE_WORDS - 1
                            pSB.Append("0" & ",")
                        Next

                        Dim sL As String = pSB.ToString
                        sL = sL.Remove(sL.Length - 1, 1)
                        Me.m_pCSV.Write_CSV_Line(sL)


                        'now write out a list of points to a single file
                        Dim lStripe As New List(Of String)
                        For iStripes As Integer = 0 To C_FCTL_TRACKDB__MAX_CONTRAST_STRIPES - 1
                            lStripe.Add("0")
                        Next
                        'save it off
                        SIL3.FileSupport.FileHelpers.File__WriteLines(Me.m_sDBDir & iCounter.ToString("00") & "__stripes.txt", lStripe)

                        'create the setpoint list
                        Dim lSet As New List(Of String)
                        For iSet As Integer = 0 To C_FCTL_TRACKDB__MAX_SETPOINTS - 1
                            lSet.Add("0")
                        Next
                        'save it off
                        SIL3.FileSupport.FileHelpers.File__WriteLines(Me.m_sDBDir & iCounter.ToString("00") & "__set_xpos.txt", lSet)
                        SIL3.FileSupport.FileHelpers.File__WriteLines(Me.m_sDBDir & iCounter.ToString("00") & "__set_veloc.txt", lSet)

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
        Public Sub InernalEvent__UDPSafe__RxPacketB(ByVal ePacketType As SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T, ByVal u16PayloadLength As SIL3.Numerical.U16, ByRef u8Payload() As Byte, ByVal u16CRC As SIL3.Numerical.U16)

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

            Dim l0 As New SIL3.ApplicationSupport.LabelHelper(10, 10, "Track Database List", MyBase.m_pInnerPanel)
            Me.m_cboDatabase = New SIL3.ApplicationSupport.ComboBoxHelper(500, l0)

            'fill
            For iCounter As Integer = 0 To Me.m_pCSV.m_alRows.Count - 1
                Dim pAL As ArrayList = Me.m_pCSV.m_alRows(iCounter)
                Me.m_cboDatabase.Threadsafe__AddItem("INDEX = " & pAL.Item(0).ToString & " DESCRIPTION = " & pAL.Item(1).ToString & " LAST EDIT = " & pAL.Item(2).ToString)
            Next

            Me.m_cboDatabase.Threadsafe__SetSelectedIndex(0)

            Dim btnChoose As New SIL3.ApplicationSupport.ButtonHelper(100, "Choose", AddressOf Me.btnChooseDB__Click)
            btnChoose.Layout__RightOfControl(Me.m_cboDatabase)

            Dim btnGenBinary As New SIL3.ApplicationSupport.ButtonHelper(100, "Gen Binary", AddressOf Me.btnGenBinary__Click)
            btnGenBinary.Layout__BelowControl(Me.m_cboDatabase)

        End Sub

#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON HELPERS"

        ''' <summary>
        ''' Choose the database
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnChooseDB__Click(s As Object, e As EventArgs)

            'assign the current index.
            Me.m_iCurrentIndex = Me.m_cboDatabase.SelectedIndex

            'see if the points file exists


        End Sub

        ''' <summary>
        ''' Generate the binary file
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnGenBinary__Click(s As Object, e As EventArgs)
            If Me.m_iCurrentIndex = -1 Then
                MsgBox("You have not selected an index yet")
                Exit Sub
            End If
            Me.Database__GenBinary(Me.m_iCurrentIndex)
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
        ''' <param name="iIndex"></param>
        Private Sub Database__GenBinary(iIndex As UInt32)

            Dim iNumStripes As UInt32 = 41
            Dim u32NumSetpoints As UInt32 = 88

            'clear the internal mem array
            vFCU_FCTL_TRACKDB_WIN32__Clear_Array()

            'setup the header
            vFCU_FCTL_TRACKDB_WIN32__Set_Header(&HABCD1234L)

            vFCU_FCTL_TRACKDB_WIN32__Set_DataLength(32)
            vFCU_FCTL_TRACKDB_WIN32__Set_TrackID(iIndex)
            vFCU_FCTL_TRACKDB_WIN32__Set_TrackStartXPos(0)
            vFCU_FCTL_TRACKDB_WIN32__Set_TrackEndXPos(1260)
            vFCU_FCTL_TRACKDB_WIN32__Set_LRF_StartXPos(0)

            vFCU_FCTL_TRACKDB_WIN32__Set_NumStripes(iNumStripes)
            For u32Counter As UInt32 = 0 To iNumStripes - 1
                vFCU_FCTL_TRACKDB_WIN32__Set_StripeStartX(u32Counter, u32Counter * 10)
            Next

            For u32Counter As UInt32 = 0 To C_FCTL_TRACKDB__HEADER_SPARE_WORDS - 1
                vFCU_FCTL_TRACKDB_WIN32__Set_HeaderSpare(u32Counter, 0)
            Next

            vFCU_FCTL_TRACKDB_WIN32__Set_Footer(&H12345678L)


            'setup the profile
            vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PusherFrontStartPos(0)
            vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PusherFrontEndPos(1200)
            vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PodFrontTargetXPos(1500)
            vFCU_FCTL_TRACKDB_WIN32__Set_Profile_NumSetpoints(u32NumSetpoints)
            For u32Counter = 0 To u32NumSetpoints - 1
                vFCU_FCTL_TRACKDB_WIN32__Set_Profile_BrakeSetpointPosX(u32Counter, u32Counter * 22)
                vFCU_FCTL_TRACKDB_WIN32__Set_Profile_BrakeSetpointVelocityX(u32Counter, u32Counter * 33)
            Next

            For u32Counter As UInt32 = 0 To C_FCTL_TRACKDB__PROFILE_SPARE_WORDS - 1
                vFCU_FCTL_TRACKDB_WIN32__Set_Profile_Spare(u32Counter, 0)
            Next

            Dim u16CRC As UInt16 = u16FCTL_TRAKDB_WIN32__ComputeCRC()
            vFCU_FCTL_TRACKDB_WIN32__Set_CRC(u16CRC)


            'do the save
            Dim u8Array() As Byte
            Dim u16Size As UInt16 = u16FCU_FCTL_TRACKDB_WIN32__Get_StructureSize()
            ReDim u8Array(u16Size - 1)

            Dim pS As New System.IO.FileStream(Me.m_sDBDir & Me.m_iCurrentIndex.ToString("00") & ".bin", IO.FileMode.Create)
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
