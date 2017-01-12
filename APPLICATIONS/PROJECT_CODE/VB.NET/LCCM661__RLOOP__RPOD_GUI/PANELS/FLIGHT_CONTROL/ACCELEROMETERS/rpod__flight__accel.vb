Namespace SIL3.rLoop.rPodControl.Panels.FlightControl

    ''' <summary>
    ''' Accelerometer control and calibration
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Accelerometers
        Inherits SIL3.ApplicationSupport.PanelTemplate

#Region "CONSTANTS"
        ''' <summary>
        ''' Number of accels on the PCB
        ''' </summary>
        Private Const C_NUM_ACCELS As Integer = 2
#End Region

#Region "MEMBERS"

        Private m_iCount As Integer
        Private m_txtCount As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtStatusFlags(C_NUM_ACCELS - 1) As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtX_Raw(C_NUM_ACCELS - 1) As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtY_Raw(C_NUM_ACCELS - 1) As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtZ_Raw(C_NUM_ACCELS - 1) As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtCRC As SIL3.ApplicationSupport.TextBoxHelper

#End Region '#Region "MEMBERS"

#Region "NEW"
        ''' <summary>
        ''' New instance
        ''' </summary>
        ''' <param name="sPanelText"></param>
        ''' <remarks></remarks>
        Public Sub New(sPanelText As String)
            MyBase.New(sPanelText)

        End Sub
#End Region '#Region "NEW"

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
        ''' New UDP packet in
        ''' </summary>
        ''' <param name="ePacketType"></param>
        ''' <param name="u16PacketLength"></param>
        ''' <param name="u8Array"></param>
        ''' <remarks></remarks>
        Public Sub InernalEvent__UDPSafe__RxPacketB(ByVal ePacketType As SIL3.SafeUDP.PacketTypes.SAFE_UDP__PACKET_T, ByVal u16PacketLength As Numerical.U16, ByRef u8Array() As Byte, ByVal u16CRC As Numerical.U16)

            If MyBase.m_bLayout = True Then

                '
                If ePacketType = SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_ACCEL__TX_CAL_DATA Then

                    Dim u32StatusFlags(C_NUM_ACCELS - 1) As Numerical.U32
                    Dim s16X_Raw(C_NUM_ACCELS - 1) As Numerical.S16
                    Dim s16Y_Raw(C_NUM_ACCELS - 1) As Numerical.S16
                    Dim s16Z_Raw(C_NUM_ACCELS - 1) As Numerical.S16

                    Dim iDevice As Integer = 0
                    Dim iOffset As Integer = 0


                    'split our packet
                    For iDevice = 0 To C_NUM_ACCELS - 1


                        u32StatusFlags(iDevice) = New Numerical.U32(u8Array, iOffset)
                        iOffset += 4

                        s16X_Raw(iDevice) = New Numerical.S16(u8Array, iOffset)
                        iOffset += 2

                        s16Y_Raw(iDevice) = New Numerical.S16(u8Array, iOffset)
                        iOffset += 2

                        s16Z_Raw(iDevice) = New Numerical.S16(u8Array, iOffset)
                        iOffset += 2

                        'update
                        Me.m_txtStatusFlags(iDevice).Threadsafe__SetText(u32StatusFlags(iDevice).To_String)
                        Me.m_txtX_Raw(iDevice).Threadsafe__SetText(s16X_Raw(iDevice).To__Int.ToString)
                        Me.m_txtY_Raw(iDevice).Threadsafe__SetText(s16Y_Raw(iDevice).To__Int.ToString)
                        Me.m_txtZ_Raw(iDevice).Threadsafe__SetText(s16Z_Raw(iDevice).To__Int.ToString)

                    Next

                    'crc
                    Me.m_txtCRC.Threadsafe__SetText(u16CRC.To_String)

                    iOffset = 0

                    Me.m_iCount += 1
                    Me.m_txtCount.Threadsafe__SetText(Me.m_iCount.ToString)


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

            Dim btnFineX(C_NUM_ACCELS - 1) As SIL3.ApplicationSupport.ButtonHelper
            Dim btnFineY(C_NUM_ACCELS - 1) As SIL3.ApplicationSupport.ButtonHelper
            Dim btnFineZ(C_NUM_ACCELS - 1) As SIL3.ApplicationSupport.ButtonHelper
            Dim btnAuto(C_NUM_ACCELS - 1) As SIL3.ApplicationSupport.ButtonHelper
            Dim btnRequest As New SIL3.ApplicationSupport.ButtonHelper(10, 10, 100, "Request", MyBase.m_pInnerPanel, AddressOf Me.btnRequest__Click)
            Dim btnStream As New SIL3.ApplicationSupport.ButtonHelper(100, "Stream", AddressOf Me.btnStream__Click)
            btnStream.Layout__RightOfControl(btnRequest)

            Dim iIndex As Integer = 0
            Dim l0 As New SIL3.ApplicationSupport.LabelHelper("Accel 0 Status Flags")
            l0.Layout__BelowControl(btnRequest)
            Me.m_txtStatusFlags(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0)
            Dim l1 As New SIL3.ApplicationSupport.LabelHelper("X Raw")
            l1.Layout__AboveRightControl(l0, Me.m_txtStatusFlags(iIndex))
            Me.m_txtX_Raw(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper(80, l1)
            btnFineX(iIndex) = New SIL3.ApplicationSupport.ButtonHelper(100, "X Fine Zero", AddressOf Me.btnFineX__Click)
            btnFineX(iIndex).Layout__RightOfControl(Me.m_txtX_Raw(iIndex))
            btnFineX(iIndex).Tag = iIndex.ToString
            Dim l2 As New SIL3.ApplicationSupport.LabelHelper("Y Raw")
            l2.Layout__AboveRightControl(l1, btnFineX(iIndex))
            Me.m_txtY_Raw(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper(80, l2)
            btnFineY(iIndex) = New SIL3.ApplicationSupport.ButtonHelper(100, "Y Fine Zero", AddressOf Me.btnFineY__Click)
            btnFineY(iIndex).Layout__RightOfControl(Me.m_txtY_Raw(iIndex))
            btnFineY(iIndex).Tag = iIndex.ToString
            Dim l3 As New SIL3.ApplicationSupport.LabelHelper("Z Raw")
            l3.Layout__AboveRightControl(l2, btnFineY(iIndex))
            Me.m_txtZ_Raw(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper(80, l3)
            btnFineZ(iIndex) = New SIL3.ApplicationSupport.ButtonHelper(100, "Z Fine Zero", AddressOf Me.btnFineZ__Click)
            btnFineZ(iIndex).Layout__RightOfControl(Me.m_txtZ_Raw(iIndex))
            btnFineZ(iIndex).Tag = iIndex.ToString
            btnAuto(iIndex) = New SIL3.ApplicationSupport.ButtonHelper(100, "Auto Cal", AddressOf Me.btnAutoCal__Click)
            btnAuto(iIndex).Layout__RightOfControl(btnFineZ(iIndex))
            btnAuto(iIndex).Tag = iIndex.ToString

            iIndex += 1
            Dim l10 As New SIL3.ApplicationSupport.LabelHelper("Accel 1 Status Flags", Me.m_txtStatusFlags(iIndex - 1))
            Me.m_txtStatusFlags(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper(100, l10)
            Dim l11 As New SIL3.ApplicationSupport.LabelHelper("X Raw")
            l11.Layout__AboveRightControl(l10, Me.m_txtStatusFlags(iIndex))
            Me.m_txtX_Raw(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper(80, l11)
            btnFineX(iIndex) = New SIL3.ApplicationSupport.ButtonHelper(100, "X Fine Zero", AddressOf Me.btnFineX__Click)
            btnFineX(iIndex).Layout__RightOfControl(Me.m_txtX_Raw(iIndex))
            btnFineX(iIndex).Tag = iIndex.ToString
            Dim l12 As New SIL3.ApplicationSupport.LabelHelper("Y Raw")
            l12.Layout__AboveRightControl(l11, btnFineX(iIndex))
            Me.m_txtY_Raw(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper(80, l12)
            btnFineY(iIndex) = New SIL3.ApplicationSupport.ButtonHelper(100, "Y Fine Zero", AddressOf Me.btnFineY__Click)
            btnFineY(iIndex).Layout__RightOfControl(Me.m_txtY_Raw(iIndex))
            btnFineY(iIndex).Tag = iIndex.ToString
            Dim l13 As New SIL3.ApplicationSupport.LabelHelper("Z Raw")
            l13.Layout__AboveRightControl(l12, btnFineY(iIndex))
            Me.m_txtZ_Raw(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper(80, l13)
            btnFineZ(iIndex) = New SIL3.ApplicationSupport.ButtonHelper(100, "Z Fine Zero", AddressOf Me.btnFineZ__Click)
            btnFineZ(iIndex).Layout__RightOfControl(Me.m_txtZ_Raw(iIndex))
            btnFineZ(iIndex).Tag = iIndex.ToString
            btnAuto(iIndex) = New SIL3.ApplicationSupport.ButtonHelper(100, "Auto Cal", AddressOf Me.btnAutoCal__Click)
            btnAuto(iIndex).Layout__RightOfControl(btnFineZ(iIndex))
            btnAuto(iIndex).Tag = iIndex.ToString

            Dim l99 As New SIL3.ApplicationSupport.LabelHelper("Packet Count")
            l99.Layout__BelowControl(Me.m_txtStatusFlags(iIndex))
            Me.m_txtCount = New SIL3.ApplicationSupport.TextBoxHelper(100, l99)
            Dim l999 As New SIL3.ApplicationSupport.LabelHelper("CRC")
            l999.Layout__AboveRightControl(l99, Me.m_txtCount)
            Me.m_txtCRC = New SIL3.ApplicationSupport.TextBoxHelper(80, l999)

        End Sub
#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON HELPERS"

        ''' <summary>
        ''' Request some data
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        ''' <remarks></remarks>
        Private Sub btnRequest__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_ACCEL__TX_CAL_DATA,
                                                 0, 0, 0, 0)
        End Sub

        ''' <summary>
        ''' Fine Zero X
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        ''' <remarks></remarks>
        Private Sub btnFineX__Click(s As Object, e As EventArgs)
            Dim oB As SIL3.ApplicationSupport.ButtonHelper = CType(s, SIL3.ApplicationSupport.ButtonHelper)
            Dim iDevice As Integer = Integer.Parse(oB.Tag.ToString)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_ACCEL__FINE_ZERO_ADJUSTMENT,
                                                 iDevice, 0, 0, 0)
        End Sub

        ''' <summary>
        ''' Fine Zero Y
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        ''' <remarks></remarks>
        Private Sub btnFineY__Click(s As Object, e As EventArgs)
            Dim oB As SIL3.ApplicationSupport.ButtonHelper = CType(s, SIL3.ApplicationSupport.ButtonHelper)
            Dim iDevice As Integer = Integer.Parse(oB.Tag.ToString)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_ACCEL__FINE_ZERO_ADJUSTMENT,
                                                 iDevice, 1, 0, 0)

        End Sub

        ''' <summary>
        ''' Fine Zero Z
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        ''' <remarks></remarks>
        Private Sub btnFineZ__Click(s As Object, e As EventArgs)
            Dim oB As SIL3.ApplicationSupport.ButtonHelper = CType(s, SIL3.ApplicationSupport.ButtonHelper)
            Dim iDevice As Integer = Integer.Parse(oB.Tag.ToString)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_ACCEL__FINE_ZERO_ADJUSTMENT,
                                                 iDevice, 2, 0, 0)

        End Sub

        ''' <summary>
        ''' Autocalibrate on channel
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        ''' <remarks></remarks>
        Private Sub btnAutoCal__Click(s As Object, e As EventArgs)
            Dim oB As SIL3.ApplicationSupport.ButtonHelper = CType(s, SIL3.ApplicationSupport.ButtonHelper)
            Dim iDevice As Integer = Integer.Parse(oB.Tag.ToString)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_ACCEL__AUTO_CALIBRATE,
                                                 iDevice, 0, 0, 0)

        End Sub


        ''' <summary>
        ''' when we want to stream data
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        ''' <remarks></remarks>
        Private Sub btnStream__Click(s As Object, e As EventArgs)

            Dim oB As SIL3.ApplicationSupport.ButtonHelper = CType(s, SIL3.ApplicationSupport.ButtonHelper)

            If oB.Text = "Stream" Then
                'start streaming
                'RaiseEvent UserEvent__USB_UDP__TxControlPacket(SIL3.SafeUDP.PacketTypes.SAFE_UDP__PACKET_T.SAFE_UDP__LCCM312__ECU__ENABLE_TIMED_PACKET, SIL3.SafeUDP.PacketTypes.SAFE_UDP__PACKET_T.SAFE_UDP__LCCM312__ECU__ACCEL_REQUEST_CAL_DATA, 0, 0, 0)
                oB.Text = "Stop Stream"
            Else
                'stop streaming
                'RaiseEvent UserEvent__USB_UDP__TxControlPacket(SIL3.SafeUDP.PacketTypes.SAFE_UDP__PACKET_T.SAFE_UDP__LCCM312__ECU__ENABLE_TIMED_PACKET, 0, 0, 0, 0)
                oB.Text = "Stream"
            End If


        End Sub

#End Region '#Region "BUTTON HELPERS"

    End Class


End Namespace
