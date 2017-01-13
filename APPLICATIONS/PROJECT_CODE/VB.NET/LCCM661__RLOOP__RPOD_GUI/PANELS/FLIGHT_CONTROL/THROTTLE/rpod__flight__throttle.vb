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
                    Dim pU32UpperFaultFlags As New SIL3.Numerical.U32(u8Payload, iOffset)
                    iOffset += 4

                    Dim pU32AMCFaultFlags As New SIL3.Numerical.U32(u8Payload, iOffset)
                    iOffset += 4

                    Dim pU16RPM((C_NUM__THROTTLES * 3) - 1) As SIL3.Numerical.U16
                    For iCounter As Integer = 0 To (C_NUM__THROTTLES * 3) - 1
                        pU16RPM(iCounter) = New SIL3.Numerical.U16(u8Payload, iOffset)
                        iOffset += 1
                    Next

                    Dim iCounter2 As Integer = 0
                    For iCounter As Integer = 0 To (C_NUM__THROTTLES) - 1
                        Me.m_txtReqRPM(iCounter).Threadsafe__SetText(pU16RPM(iCounter2).To__Int.ToString)
                        iCounter2 += 1
                    Next
                    For iCounter As Integer = 0 To (C_NUM__THROTTLES) - 1
                        Me.m_txtActRPM(iCounter).Threadsafe__SetText(pU16RPM(iCounter2).To__Int.ToString)
                        iCounter2 += 1
                    Next
                    For iCounter As Integer = 0 To (C_NUM__THROTTLES) - 1
                        Me.m_txtASIRPM(iCounter).Threadsafe__SetText(pU16RPM(iCounter2).To__Int.ToString)
                        iCounter2 += 1
                    Next

                    Me.m_txtThrottleFlags.Flags__Update(pU32UpperFaultFlags, True)
                    Me.m_txtAMC7812Flags.Flags__Update(pU32AMCFaultFlags, True)

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
            Dim btnRequest As New SIL3.ApplicationSupport.ButtonHelper(100, "Request", AddressOf btnRequest_L0__Click)
            btnRequest.Layout__BelowControl(l0)
            Dim btnStreamOn As New SIL3.ApplicationSupport.ButtonHelper(100, "Stream On", AddressOf btnStreamOn__Click)
            btnStreamOn.Layout__RightOfControl(btnRequest)
            Dim btnStreamOff As New SIL3.ApplicationSupport.ButtonHelper(100, "Stream Off", AddressOf btnStreamOff__Clock)
            btnStreamOff.Layout__RightOfControl(btnStreamOn)

            Dim l110 As New SIL3.ApplicationSupport.LabelHelper("Rx Count")
            l110.Layout__AboveRightControl(l0, btnStreamOff)
            Me.m_txtRxCount = New SIL3.ApplicationSupport.TextBoxHelper(100, l110)

            Dim l10 As New SIL3.ApplicationSupport.LabelHelper("Module Flags")
            l10.Layout__BelowControl(btnRequest)
            Me.m_txtThrottleFlags = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l10)
            Dim l11 As New SIL3.ApplicationSupport.LabelHelper("AMC7812 Flags")
            l11.Layout__AboveRightControl(l10, Me.m_txtThrottleFlags)
            Me.m_txtAMC7812Flags = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l11)

            Dim la(C_NUM__THROTTLES) As SIL3.ApplicationSupport.LabelHelper

            For iCounter As Integer = 0 To C_NUM__THROTTLES - 1
                la(iCounter) = New SIL3.ApplicationSupport.LabelHelper("Requested RPM:" & iCounter.ToString)
                If iCounter = 0 Then
                    la(iCounter).Layout__BelowControl(Me.m_txtThrottleFlags)
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

        End Sub

#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON HELPERS"

        Private Sub btnStreamOn__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__STREAMING_CONTROL,
                                                 1, SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_THROTTLE__TX_DATA, 0, 0)
        End Sub

        Private Sub btnStreamOff__Clock(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__STREAMING_CONTROL,
                                                 0, 0, 0, 0)
        End Sub

        ''' <summary>
        ''' Request laser0 contrast data
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnRequest_L0__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LASER_CONT__REQUEST_LASER_DATA,
                                                 0, 0, 0, 0)
        End Sub
        Private Sub btnRequest_L1__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LASER_CONT__REQUEST_LASER_DATA,
                                                 1, 0, 0, 0)
        End Sub
        Private Sub btnRequest_L2__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LASER_CONT__REQUEST_LASER_DATA,
                                                 2, 0, 0, 0)
        End Sub



#End Region '#Region "BUTTON HELPERS"

    End Class


End Namespace
