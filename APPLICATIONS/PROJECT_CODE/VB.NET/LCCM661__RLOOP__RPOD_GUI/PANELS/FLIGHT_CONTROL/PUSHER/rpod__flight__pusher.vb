Namespace SIL3.rLoop.rPodControl.Panels.FlightControl

    ''' <summary>
    ''' Pusher Interface System
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Pusher
        Inherits SIL3.ApplicationSupport.PanelTemplate

#Region "CONSTANTS"
#End Region '#Region "CONSTANTS"

#Region "MEMBERS"

        Private m_iRxCount As Integer
        Private m_txtRxCount As SIL3.ApplicationSupport.TextBoxHelper

        Private m_txtFlags As SIL3.ApplicationSupport.TextBoxHelper_FaultFlags
        Private m_txtState As SIL3.ApplicationSupport.TextBoxHelper_StateDisplay
        Private m_txtEdgeFlags(2 - 1) As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtSwitchState(2 - 1) As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtTimer As SIL3.ApplicationSupport.TextBoxHelper

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
            Me.m_sLogDir = Me.m_sLogDir & "PUSHER\"

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
                If ePacketType = SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_PUSH__TX_PUSHER_DATA Then

                    Dim iOffset As Integer = 0
                    iOffset += Me.m_txtFlags.Flags__Update(u8Payload, iOffset, True)
                    Me.m_txtState.Value__Update(u8Payload(iOffset))
                    iOffset += 1
                    Dim u8SW0_Edge As New SIL3.Numerical.U8(u8Payload, iOffset)
                    iOffset += 1
                    Dim u8SW1_Edge As New SIL3.Numerical.U8(u8Payload, iOffset)
                    iOffset += 1
                    Dim u8SW0_State As New SIL3.Numerical.U8(u8Payload, iOffset)
                    iOffset += 1
                    Dim u8SW1_State As New SIL3.Numerical.U8(u8Payload, iOffset)
                    iOffset += 1
                    Dim pU32Timer As New SIL3.Numerical.U32(u8Payload, iOffset)
                    iOffset += 4



                    Me.m_txtEdgeFlags(0).Threadsafe__SetText(u8SW0_Edge.To_String)
                    Me.m_txtEdgeFlags(1).Threadsafe__SetText(u8SW1_Edge.To_String)
                    Me.m_txtSwitchState(0).Threadsafe__SetText(u8SW0_State.To_String)
                    Me.m_txtSwitchState(1).Threadsafe__SetText(u8SW1_State.To_String)
                    Me.m_txtTimer.Threadsafe__SetText(pU32Timer.To__Int.ToString)

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
            Dim btnRL0 As New SIL3.ApplicationSupport.ButtonHelper(100, "Stream On", AddressOf btnStream__Click)
            btnRL0.Layout__BelowControl(l0)

            Dim l1 As New SIL3.ApplicationSupport.LabelHelper("Rx Count")
            l1.Layout__AboveRightControl(l0, btnRL0)
            Me.m_txtRxCount = New SIL3.ApplicationSupport.TextBoxHelper(100, l1)

            Dim l2 As New SIL3.ApplicationSupport.LabelHelper("Fault Flags")
            l2.Layout__BelowControl(btnRL0)
            Me.m_txtFlags = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l2)

            Dim l22 As New SIL3.ApplicationSupport.LabelHelper("Pin Final State")
            l22.Layout__BelowControl(Me.m_txtFlags)
            Me.m_txtState = New SIL3.ApplicationSupport.TextBoxHelper_StateDisplay(250, l22)
            Me.m_txtState.States__Add("PIN_FINAL_STATE__DISCONNECTED")
            Me.m_txtState.States__Add("PIN_FINAL_STATE__CONNECTED")
            Me.m_txtState.States__Add("PIN_FINAL_STATE__UNKNOWN")


            Dim l3 As New SIL3.ApplicationSupport.LabelHelper("Sw:0 Edge")
            l3.Layout__BelowControl(Me.m_txtState)
            Me.m_txtEdgeFlags(0) = New SIL3.ApplicationSupport.TextBoxHelper(100, l3)
            Dim l4 As New SIL3.ApplicationSupport.LabelHelper("Sw:1 Edge")
            l4.Layout__AboveRightControl(l3, Me.m_txtEdgeFlags(0))
            Me.m_txtEdgeFlags(1) = New SIL3.ApplicationSupport.TextBoxHelper(100, l4)

            Dim l5 As New SIL3.ApplicationSupport.LabelHelper("Sw:0 State")
            l5.Layout__BelowControl(Me.m_txtEdgeFlags(0))
            Me.m_txtSwitchState(0) = New SIL3.ApplicationSupport.TextBoxHelper(100, l5)
            Dim l6 As New SIL3.ApplicationSupport.LabelHelper("Sw:1 State")
            l6.Layout__AboveRightControl(l5, Me.m_txtSwitchState(0))
            Me.m_txtSwitchState(1) = New SIL3.ApplicationSupport.TextBoxHelper(100, l6)

            Dim l7 As New SIL3.ApplicationSupport.LabelHelper("Timer")
            l7.Layout__BelowControl(Me.m_txtSwitchState(0))
            Me.m_txtTimer = New SIL3.ApplicationSupport.TextBoxHelper(100, l7)


        End Sub

#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON HELPERS"

        ''' <summary>
        ''' control streaming
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnStream__Click(s As Object, e As EventArgs)

            Dim pSB As SIL3.ApplicationSupport.ButtonHelper = CType(s, SIL3.ApplicationSupport.ButtonHelper)

            If pSB.Text = "Stream On" Then
                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__STREAMING_CONTROL,
                                                 1, SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_PUSH__TX_PUSHER_DATA, 0, 0)
                pSB.Text = "Stream OFF"
            Else
                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__STREAMING_CONTROL,
                                                 0, SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_PUSH__TX_PUSHER_DATA, 0, 0)
                pSB.Text = "Stream On"
            End If

        End Sub


#End Region '#Region "BUTTON HELPERS"

    End Class


End Namespace
