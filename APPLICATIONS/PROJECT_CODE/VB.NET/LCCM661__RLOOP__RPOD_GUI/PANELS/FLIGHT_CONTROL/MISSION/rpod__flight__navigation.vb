Namespace SIL3.rLoop.rPodControl.Panels.FlightControl

    ''' <summary>
    ''' Primary Navigation Page
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Navigation
        Inherits LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.PanelTemplate

#Region "CONSTANTS"

        ''' <summary>
        ''' Total number in FCU, don't change
        ''' </summary>
        Private Const C_NUM_TRACK_DATABASES As Integer = 8

#End Region '#Region "CONSTANTS"

#Region "MEMBERS"

        Private m_iRxCount As Integer
        Private m_txtRxCount As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper

        Private m_txtFlags As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags
        Private m_txtPodHealth As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags
        Private m_txtMissionPhase As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_StateDisplay
        Private m_txtDistFilt As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper

        Private m_cboSelectTrackDB As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ComboBoxHelper
        Private m_txtCurrentTrackDB As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U8

        ''' <summary>
        ''' The logging directory
        ''' </summary>
        Private m_sLogDir As String


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
            Me.m_sLogDir = Me.m_sLogDir & "MISSION\"
            If Me.m_sLogDir.Contains(":\") = True Then
                LAPP188__RLOOP__LIB.SIL3.FileSupport.FileHelpers.Folder__CheckWarnMake(Me.m_sLogDir, True)
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

                'match thepacket
                If ePacketType = SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__TX_MISSION_DATA Then

                    Dim iOffset As Integer = 0

                    'update the GUI
                    iOffset += Me.m_txtFlags.Flags__Update(u8Payload, iOffset, True)
                    Me.m_txtMissionPhase.Value__Update(New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(u8Payload, iOffset).To__Int)
                    iOffset += 2
                    iOffset += Me.m_txtCurrentTrackDB.Value__Update(u8Payload, iOffset)
                    iOffset += Me.m_txtPodHealth.Flags__Update(u8Payload, iOffset, True)

                    Me.m_iRxCount += 1
                    Me.m_txtRxCount.Threadsafe__SetText(Me.m_iRxCount.ToString)


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


            Dim l0 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper(10, 10, "Streaming Control", MyBase.m_pInnerPanel)
            Dim btnOn As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Stream On", AddressOf btnStreamOn__Click)
            btnOn.Layout__BelowControl(l0)

            Dim l11 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Rx Count")
            l11.Layout__AboveRightControl(l0, btnOn)
            Me.m_txtRxCount = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper(100, l11)
            Me.m_txtRxCount.ReadOnly = True

            Dim l00 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Fault Flags")
            l00.Layout__AboveRightControl(l11, Me.m_txtRxCount)
            Me.m_txtFlags = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l00)
            Me.m_txtFlags.FlagsFile__Read("../../../../FIRMWARE/PROJECT_CODE/LCCM655__RLOOP__FCU_CORE/FAULTS/fcu__faults__fault_flags.h", "FAULTS")


            Dim l01 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Pod Health")
            l01.Layout__AboveRightControl(l00, Me.m_txtFlags)
            Me.m_txtPodHealth = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l01)
            Me.m_txtPodHealth.Flags__Add("P0: BATTERY_PACK_TEMP_RANGE")
            Me.m_txtPodHealth.Flags__Add("P1: BATTERY_CELL_TEMP_RANGE")
            Me.m_txtPodHealth.Flags__Add("P2: BATTERY_VOLTAGE_RANGE")
            Me.m_txtPodHealth.Flags__Add("P3: BATTERY_CELL_VOLTAGE_RANGE")
            Me.m_txtPodHealth.Flags__Add("P4: BATTERY_CURRENT_RANGE")
            Me.m_txtPodHealth.Flags__Add("P5: HE_TEMP_RANGE")
            Me.m_txtPodHealth.Flags__Add("P6: HE_CURRENT_RANGE")
            Me.m_txtPodHealth.Flags__Add("P7: HE_VOLT_RANGE")
            Me.m_txtPodHealth.Flags__Add("P8: HE_RPM_RANGE")
            Me.m_txtPodHealth.Flags__Add("P9: PV_PRESS_RANGE")
            Me.m_txtPodHealth.Flags__Add("P10: PV_TEMP_RANGE")

            Dim l02 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Mission State")
            l02.Layout__AboveRightControl(l01, Me.m_txtPodHealth)
            Me.m_txtMissionPhase = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_StateDisplay(200, l02)
            Me.m_txtMissionPhase.ReadOnly = True
            Me.m_txtMissionPhase.HeaderFile__Set("../../../../FIRMWARE/PROJECT_CODE/LCCM655__RLOOP__FCU_CORE/FLIGHT_CONTROLLER/fcu__flight_controller__state_types.h", "TE_POD_STATE_T")




            Dim l110 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Flight Controls", btnOn)

            Dim btnEnterPreRun As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Enter Pre-Run", Nothing)
            btnEnterPreRun.Layout__BelowControl(l110)
            'btnEnterPreRun.BackColor = Color.Orange
            Dim btnFlightAbort As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Flight Abort", Nothing)
            btnFlightAbort.Layout__RightOfControl(btnEnterPreRun)
            Dim btnPodStop As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Pod Stop", AddressOf Me.btnPodStop__Click)
            btnPodStop.Layout__RightOfControl(btnFlightAbort)
            Dim btnPodSafe As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Pod Safe", AddressOf Me.btnPodSafed__Click)
            btnPodSafe.Layout__RightOfControl(btnPodStop)



            Dim l2 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Select Track DB", btnEnterPreRun)
            Me.m_cboSelectTrackDB = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ComboBoxHelper(100, l2)

            For iCounter As Integer = 0 To C_NUM_TRACK_DATABASES - 1
                Me.m_cboSelectTrackDB.Threadsafe__AddItem(iCounter.ToString)
            Next
            Me.m_cboSelectTrackDB.Threadsafe__SetSelectedIndex(0)

            Dim l3 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Current Track DB")
            l3.Layout__AboveRightControl(l2, Me.m_cboSelectTrackDB)
            Me.m_txtCurrentTrackDB = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U8(100, l3)

            Dim btnChangeTrackDB As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Change DB", AddressOf Me.btnChangeTrackDB__Click)
            btnChangeTrackDB.Layout__RightOfControl(Me.m_txtCurrentTrackDB)

        End Sub

#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON HELPERS"

        ''' <summary>
        ''' Change the current track database
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnChangeTrackDB__Click(s As Object, e As EventArgs)
            Dim u32Index As UInt32 = Me.m_cboSelectTrackDB.SelectedIndex
            If MsgBox("Warn: You are about to change the track ID to: " & u32Index.ToString & " Continue?", MsgBoxStyle.YesNo) = MsgBoxResult.Yes Then
                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_FLT__SELECT_TRACK_DB,
                                                 &H11223344, u32Index, 0, 0)
            End If
        End Sub

        ''' <summary>
        ''' Enable mission streaming
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnStreamOn__Click(s As Object, e As EventArgs)
            Dim pSB As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper = CType(s, LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper)

            If pSB.Text = "Stream On" Then
                pSB.Text = "Stream Off"
                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__STREAMING_CONTROL,
                                                 1, SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__TX_MISSION_DATA, 0, 0)
            Else
                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__STREAMING_CONTROL,
                                                 0, SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__TX_MISSION_DATA, 0, 0)
                pSB.Text = "Stream On"
            End If

        End Sub




        ''' <summary>
        ''' Transmit our pod safed command to power nodes, kills all power
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnPodSafed__Click(s As Object, e As EventArgs)

            If MsgBox("Warning: This will Safe the pod" & Environment.NewLine & "All power will be lost, Continue?", MsgBoxStyle.OkCancel, "Pod Safe Command") = MsgBoxResult.Ok Then
                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__POWER_A,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__PWR_GEN__POD_SAFE_COMMAND,
                                                 &H76543210L, 0, 0, 0)

            End If

        End Sub

        ''' <summary>
        ''' Do the pod stop command
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnPodStop__Click(s As Object, e As EventArgs)

            If MsgBox("Warning: This will STOP the pod, Brakes Activated!" & Environment.NewLine & "Continue?", MsgBoxStyle.OkCancel, "Pod Safe Command") = MsgBoxResult.Ok Then
                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__POWER_A,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__POD_STOP_COMMAND,
                                                 &H1234ABCDL, 0, 0, 0)

            End If

        End Sub

        Private Sub btnChangeState_Test__Click(s As Object, e As EventArgs)

            If MsgBox("Warning: This will put the pod into TEST_STATE!" & Environment.NewLine & "Continue?", MsgBoxStyle.OkCancel, "Pod Safe Command") = MsgBoxResult.Ok Then
                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__POWER_A,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__POD_STOP_COMMAND,
                                                 &H1234ABCDL, 0, 0, 0)

            End If

        End Sub

#End Region '#Region "BUTTON HELPERS"

    End Class


End Namespace
