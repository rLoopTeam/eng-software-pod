Namespace SIL3.rLoop.rPodControl.Panels.FlightControl

    ''' <summary>
    ''' Throttle Subsystem
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Throttle
        Inherits SIL3.ApplicationSupport.PanelTemplate

#Region "CONSTANTS"
        Private Const C_NUM__THROTTLES As Integer = 8
#End Region '#Region "CONSTANTS"

#Region "MEMBERS"

        Private m_iRxCount As Integer
        Private m_txtRxCount As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtThrottleFlags As SIL3.ApplicationSupport.TextBoxHelper_FaultFlags
        Private m_txtAMC7812Flags As SIL3.ApplicationSupport.TextBoxHelper_FaultFlags

        Private m_txtReqRPM(C_NUM__THROTTLES - 1) As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtActRPM(C_NUM__THROTTLES - 1) As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtASIRPM(C_NUM__THROTTLES - 1) As SIL3.ApplicationSupport.TextBoxHelper

        Private m_cboHE As SIL3.ApplicationSupport.ComboBoxHelper
        Private m_cboMode As SIL3.ApplicationSupport.ComboBoxHelper
        Private m_txtSetRPM As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtThrottleState As SIL3.ApplicationSupport.TextBoxHelper_StateDisplay
        Private m_txtAMC7812State As SIL3.ApplicationSupport.TextBoxHelper_StateDisplay
        Private m_txtIndex As SIL3.ApplicationSupport.TextBoxHelper

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
            Me.m_sLogDir = Me.m_sLogDir & "THROTTLE\"

            'check our folder
            SIL3.FileSupport.FileHelpers.Folder__CheckWarnMake(Me.m_sLogDir)


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
                If ePacketType = SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_THROTTLE__TX_DATA Then

                    Dim iOffset As Integer = 0
                    iOffset += Me.m_txtThrottleFlags.Flags__Update(u8Payload, iOffset, True)
                    iOffset += Me.m_txtAMC7812Flags.Flags__Update(u8Payload, iOffset, True)


                    Dim pU16RPM((C_NUM__THROTTLES * 3) - 1) As SIL3.Numerical.U16
                    For iCounter As Integer = 0 To (C_NUM__THROTTLES * 3) - 1
                        pU16RPM(iCounter) = New SIL3.Numerical.U16(u8Payload, iOffset)
                        iOffset += 2
                    Next

                    Dim pU8State As New SIL3.Numerical.U8(u8Payload, iOffset)
                    iOffset += 1
                    Me.m_txtThrottleState.Value__Update(pU8State.To__Int)

                    Dim pU8Index As New SIL3.Numerical.U8(u8Payload, iOffset)
                    iOffset += 1
                    Me.m_txtIndex.Threadsafe__SetText(pU8Index.To__Int.ToString)

                    Me.m_txtAMC7812State.Value__Update(u8Payload(iOffset))
                    iOffset += 1


                    Dim iCounter2 As Integer = 0
                    For iCounter As Integer = 0 To (C_NUM__THROTTLES) - 1
                        Dim sPrev As String = Me.m_txtReqRPM(iCounter).Text
                        Me.m_txtReqRPM(iCounter).Threadsafe__SetText(pU16RPM(iCounter2).To__Int.ToString)
                        If Me.m_txtReqRPM(iCounter).Text <> sPrev Then
                            Me.m_txtReqRPM(iCounter).Fade__Colour(Color.Blue)
                        End If
                        iCounter2 += 1
                    Next
                    For iCounter As Integer = 0 To (C_NUM__THROTTLES) - 1
                        Dim sPrev As String = Me.m_txtActRPM(iCounter).Text
                        Me.m_txtActRPM(iCounter).Threadsafe__SetText(pU16RPM(iCounter2).To__Int.ToString)
                        If Me.m_txtActRPM(iCounter).Text <> sPrev Then
                            Me.m_txtActRPM(iCounter).Fade__Colour(Color.Blue)
                        End If
                        iCounter2 += 1
                    Next
                    For iCounter As Integer = 0 To (C_NUM__THROTTLES) - 1
                        Me.m_txtASIRPM(iCounter).Threadsafe__SetText(pU16RPM(iCounter2).To__Int.ToString)
                        iCounter2 += 1
                    Next




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

            Dim l0 As New SIL3.ApplicationSupport.LabelHelper(10, 10, "Controls", MyBase.m_pInnerPanel)
            Dim btnRequest As New SIL3.ApplicationSupport.ButtonHelper(100, "Request", AddressOf btnRequest__Click)
            btnRequest.Layout__BelowControl(l0)
            Dim btnStreamOn As New SIL3.ApplicationSupport.ButtonHelper(100, "Stream On", AddressOf btnStreamOn__Click)
            btnStreamOn.Layout__RightOfControl(btnRequest)
            Dim l110 As New SIL3.ApplicationSupport.LabelHelper("Rx Count")
            l110.Layout__AboveRightControl(l0, btnStreamOn)
            Me.m_txtRxCount = New SIL3.ApplicationSupport.TextBoxHelper(100, l110)

            Dim l10 As New SIL3.ApplicationSupport.LabelHelper("Module Flags")
            l10.Layout__BelowControl(btnRequest)
            Me.m_txtThrottleFlags = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l10)

            Me.m_txtThrottleFlags.Flags__Add("GENERAL")
            Me.m_txtThrottleFlags.Flags__Add("AMC7812 FAULT")
            Me.m_txtThrottleFlags.Flags__Add("INDEXING FAULT")
            Me.m_txtThrottleFlags.Flags__Add("THROTTLE NOT IN RUN MODE")
            Me.m_txtThrottleFlags.Flags__Add("DEV MODE ENABLED")


            Dim l11 As New SIL3.ApplicationSupport.LabelHelper("AMC7812 Flags")
            l11.Layout__AboveRightControl(l10, Me.m_txtThrottleFlags)
            Me.m_txtAMC7812Flags = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l11)
            Me.m_txtThrottleFlags.Flags__Add("GENERAL")
            Me.m_txtThrottleFlags.Flags__Add("DAC INDEXING FAULT ")
            Me.m_txtThrottleFlags.Flags__Add("I2C FAULT")



            Dim l10a As New SIL3.ApplicationSupport.LabelHelper("Throtte State")
            l10a.Layout__BelowControl(Me.m_txtThrottleFlags)
            Me.m_txtThrottleState = New ApplicationSupport.TextBoxHelper_StateDisplay(200, l10a)

            'add the states
            Me.m_txtThrottleState.States__Add("THROTTLE_STATE__IDLE")
            Me.m_txtThrottleState.States__Add("THROTTLE_STATE__RUN")
            Me.m_txtThrottleState.States__Add("THROTTLE_STATE__STEP")
            Me.m_txtThrottleState.States__Add("THROTTLE_STATE__RAMP_UP")
            Me.m_txtThrottleState.States__Add("THROTTLE_STATE__RAMP_DOWN")
            Me.m_txtThrottleState.States__Add("THROTTLE_STATE__INC_INDEX")
            Me.m_txtThrottleState.States__Add("THROTTLE_STATE__ERROR")

            Dim l10b As New SIL3.ApplicationSupport.LabelHelper("Run Index")
            l10b.Layout__AboveRightControl(l10a, Me.m_txtThrottleState)
            Me.m_txtIndex = New ApplicationSupport.TextBoxHelper(100, l10b)

            Dim l10c As New SIL3.ApplicationSupport.LabelHelper("AMC7812 State")
            l10c.Layout__AboveRightControl(l10b, Me.m_txtIndex)
            Me.m_txtAMC7812State = New ApplicationSupport.TextBoxHelper_StateDisplay(200, l10c)

            'add the AMC7812 states
            Me.m_txtAMC7812State.States__Add("AMC7812_STATE__RESET")
            Me.m_txtAMC7812State.States__Add("AMC7812_STATE__CONFIGURE_DAC")
            Me.m_txtAMC7812State.States__Add("AMC7812_STATE__IDLE")
            Me.m_txtAMC7812State.States__Add("AMC7812_STATE__UPDATE_DAC")
            Me.m_txtAMC7812State.States__Add("AMC7812_STATE__FAULT")

            Dim la(C_NUM__THROTTLES) As SIL3.ApplicationSupport.LabelHelper

            For iCounter As Integer = 0 To C_NUM__THROTTLES - 1
                la(iCounter) = New SIL3.ApplicationSupport.LabelHelper("Requested RPM:" & iCounter.ToString)
                If iCounter = 0 Then
                    la(iCounter).Layout__BelowControl(Me.m_txtThrottleState)
                Else
                    la(iCounter).Layout__AboveRightControl(la(iCounter - 1), Me.m_txtReqRPM(iCounter - 1))
                End If

                Me.m_txtReqRPM(iCounter) = New ApplicationSupport.TextBoxHelper(100, la(iCounter))
            Next


            Dim lb(C_NUM__THROTTLES) As SIL3.ApplicationSupport.LabelHelper
            For iCounter As Integer = 0 To C_NUM__THROTTLES - 1
                lb(iCounter) = New SIL3.ApplicationSupport.LabelHelper("Actual RPM:" & iCounter.ToString)
                If iCounter = 0 Then
                    lb(iCounter).Layout__BelowControl(Me.m_txtReqRPM(0))
                Else
                    lb(iCounter).Layout__AboveRightControl(lb(iCounter - 1), Me.m_txtActRPM(iCounter - 1))
                End If

                Me.m_txtActRPM(iCounter) = New ApplicationSupport.TextBoxHelper(100, lb(iCounter))
            Next

            Dim lc(C_NUM__THROTTLES) As SIL3.ApplicationSupport.LabelHelper
            For iCounter As Integer = 0 To C_NUM__THROTTLES - 1
                lc(iCounter) = New SIL3.ApplicationSupport.LabelHelper("ASI RPM:" & iCounter.ToString)
                If iCounter = 0 Then
                    lc(iCounter).Layout__BelowControl(Me.m_txtActRPM(0))
                Else
                    lc(iCounter).Layout__AboveRightControl(lc(iCounter - 1), Me.m_txtASIRPM(iCounter - 1))
                End If

                Me.m_txtASIRPM(iCounter) = New ApplicationSupport.TextBoxHelper(100, lc(iCounter))
            Next

            Dim btnEnableDev As New SIL3.ApplicationSupport.ButtonHelper(100, "Enable Dev", AddressOf Me.btnEnableDev__Click)
            btnEnableDev.Layout__BelowControl(Me.m_txtASIRPM(0))
            btnEnableDev.ToolTip__Set("Enable Development Mode", "You need Dev mode enabled to manually adjust throttles")

            Dim l90 As New SIL3.ApplicationSupport.LabelHelper("Throttle Index")
            l90.Layout__BelowControl(btnEnableDev)
            Me.m_cboHE = New SIL3.ApplicationSupport.ComboBoxHelper(100)
            Me.m_cboHE.Layout__BelowControl(l90)
            For iCounter As Integer = 0 To C_NUM__THROTTLES - 1
                Me.m_cboHE.Threadsafe__AddItem(iCounter.ToString)
            Next
            Me.m_cboHE.Threadsafe__AddItem("ALL")
            Me.m_cboHE.Threadsafe__SetSelectedIndex(0)

            Dim l91 As New SIL3.ApplicationSupport.LabelHelper("Throttle Mode")
            l91.Layout__AboveRightControl(l90, Me.m_cboHE)
            Me.m_cboMode = New SIL3.ApplicationSupport.ComboBoxHelper(100, l91)
            Me.m_cboMode.Threadsafe__AddItem("STEP")
            Me.m_cboMode.Threadsafe__AddItem("RAMP")
            Me.m_cboMode.Threadsafe__SetSelectedIndex(0)

            Dim l92 As New SIL3.ApplicationSupport.LabelHelper("Target RPM")
            l92.Layout__AboveRightControl(l91, Me.m_cboMode)
            Me.m_txtSetRPM = New ApplicationSupport.TextBoxHelper(100, l92)
            Me.m_txtSetRPM.Threadsafe__SetText("0")

            Dim btnChange As New SIL3.ApplicationSupport.ButtonHelper(100, "Change", AddressOf Me.btnChange__Click)
            btnChange.Layout__RightOfControl(Me.m_txtSetRPM)


        End Sub

#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON HELPERS"

        ''' <summary>
        ''' Switch on streaming
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnStreamOn__Click(s As Object, e As EventArgs)
            Dim pSB As SIL3.ApplicationSupport.ButtonHelper = CType(s, SIL3.ApplicationSupport.ButtonHelper)

            If pSB.Text = "Stream On" Then
                pSB.Text = "Stream Off"
                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__STREAMING_CONTROL,
                                                 1, SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_THROTTLE__TX_DATA, 0, 0)
            Else
                pSB.Text = "Stream On"
                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__STREAMING_CONTROL,
                                                 0, SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_THROTTLE__TX_DATA, 0, 0)

            End If

        End Sub




        ''' <summary>
        ''' Request one packet
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnRequest__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_THROTTLE__REQUEST_DATA,
                                                 0, 0, 0, 0)
        End Sub


        ''' <summary>
        ''' Switch on throttles dev mode.
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnEnableDev__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_THROTTLE__ENABLE_DEV_MODE,
                                                 &H11223344L, 0, 0, 0)
        End Sub


        Private Sub btnChange__Click(s As Object, e As EventArgs)

            Dim iHE As Integer = Me.m_cboHE.SelectedIndex
            If iHE < 0 Then
                MsgBox("Error: Invalid HE Index")
                Exit Sub
            End If

            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_THROTTLE__SET_RAW_THROTTLE,
                                                 iHE,
                                                 UInt32.Parse(Me.m_txtSetRPM.Text),
                                                 Me.m_cboMode.SelectedIndex, 0)
        End Sub



#End Region '#Region "BUTTON HELPERS"

    End Class


End Namespace
