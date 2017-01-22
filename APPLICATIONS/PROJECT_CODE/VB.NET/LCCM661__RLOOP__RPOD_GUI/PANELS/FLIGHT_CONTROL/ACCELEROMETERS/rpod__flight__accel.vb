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

        Private Const C_ACCEL_FREQ_HZ As Integer = 100

#End Region '#Region "CONSTANTS"

#Region "MEMBERS"

        Private m_iCount As Integer
        Private m_txtCount As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtStatusFlags(C_NUM_ACCELS - 1) As SIL3.ApplicationSupport.TextBoxHelper_FaultFlags
        Private m_txtX_Raw(C_NUM_ACCELS - 1) As SIL3.ApplicationSupport.TextBoxHelper_S16
        Private m_txtY_Raw(C_NUM_ACCELS - 1) As SIL3.ApplicationSupport.TextBoxHelper_S16
        Private m_txtZ_Raw(C_NUM_ACCELS - 1) As SIL3.ApplicationSupport.TextBoxHelper_S16
        Private m_txtCRC As SIL3.ApplicationSupport.TextBoxHelper

        Private m_txtCalc__CurrentAccel_mmss(C_NUM_ACCELS - 1) As SIL3.ApplicationSupport.TextBoxHelper_S32
        Private m_txtCalc__CurrentVeloc_mms(C_NUM_ACCELS - 1) As SIL3.ApplicationSupport.TextBoxHelper_S32
        'Private m_txtCalc__PrevVeloc_mms(C_NUM_ACCELS - 1) As SIL3.ApplicationSupport.TextBoxHelper_S32
        Private m_txtCalc__CurrentDisplacement_mm(C_NUM_ACCELS - 1) As SIL3.ApplicationSupport.TextBoxHelper_S32
        'Private m_txtCalc__PrevDisplacement_mm(C_NUM_ACCELS - 1) As SIL3.ApplicationSupport.TextBoxHelper_S32

        ''' <summary>
        ''' Our DAQ Receiver
        ''' </summary>
        Private m_pDAQ As SIL3.DAQ.Top

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
            Me.m_sLogDir = Me.m_sLogDir & "ACCEL\"

            'check our folder
            SIL3.FileSupport.FileHelpers.Folder__CheckWarnMake(Me.m_sLogDir)

            Me.m_pDAQ = New SIL3.DAQ.Top()

            'add the contrast DAQ items
            Me.m_pDAQ.DAQ__Set_LogFilePath(Me.m_sLogDir)

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
        ''' <param name="u8Payload"></param>
        ''' <remarks></remarks>
        Public Sub InernalEvent__UDPSafe__RxPacketB(ByVal ePacketType As SIL3.SafeUDP.PacketTypes.SAFE_UDP__PACKET_T, ByVal u16PayloadLength As Numerical.U16, ByRef u8Payload() As Byte, ByVal u16CRC As Numerical.U16)

            If MyBase.m_bLayout = True Then

                'cal data
                If ePacketType = SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_ACCEL__TX_CAL_DATA Then

                    Dim iOffset As Integer = 0

                    'split our packet
                    For iDevice As Integer = 0 To C_NUM_ACCELS - 1
                        'update
                        iOffset += Me.m_txtStatusFlags(iDevice).Flags__Update(u8Payload, iOffset, True)
                        iOffset += Me.m_txtX_Raw(iDevice).Value__Update(u8Payload, iOffset)
                        iOffset += Me.m_txtY_Raw(iDevice).Value__Update(u8Payload, iOffset)
                        iOffset += Me.m_txtZ_Raw(iDevice).Value__Update(u8Payload, iOffset)
                    Next

                    'crc
                    Me.m_txtCRC.Threadsafe__SetText(u16CRC.To_String)
                    Me.m_iCount += 1
                    Me.m_txtCount.Threadsafe__SetText(Me.m_iCount.ToString)


                ElseIf ePacketType = SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_ACCEL__TX_FULL_DATA Then


                    Dim iOffset As Integer = 0

                    'split our packet
                    For iDevice As Integer = 0 To C_NUM_ACCELS - 1

                        'update
                        iOffset += Me.m_txtStatusFlags(iDevice).Flags__Update(u8Payload, iOffset, True)
                        iOffset += Me.m_txtX_Raw(iDevice).Value__Update(u8Payload, iOffset)
                        iOffset += Me.m_txtY_Raw(iDevice).Value__Update(u8Payload, iOffset)
                        iOffset += Me.m_txtZ_Raw(iDevice).Value__Update(u8Payload, iOffset)

                        '5x
                        iOffset += 5 * 4

                        iOffset += Me.m_txtCalc__CurrentAccel_mmss(iDevice).Value__Update(u8Payload, iOffset)
                        iOffset += Me.m_txtCalc__CurrentVeloc_mms(iDevice).Value__Update(u8Payload, iOffset)
                        iOffset += 4 'Me.m_txtCalc__PrevVeloc_mms(iDevice).Value__Update(u8Array, iOffset)
                        iOffset += Me.m_txtCalc__CurrentDisplacement_mm(iDevice).Value__Update(u8Payload, iOffset)
                        iOffset += 4 ' Me.m_txtCalc__PrevDisplacement_mm(iDevice).Value__Update(u8Array, iOffset)

                    Next

                    'crc
                    Me.m_txtCRC.Threadsafe__SetText(u16CRC.To_String)
                    Me.m_iCount += 1
                    Me.m_txtCount.Threadsafe__SetText(Me.m_iCount.ToString)

                ElseIf ePacketType >= SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_DAQ__OFFSET_INDEX And ePacketType <= SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_DAQ__OFFSET_INDEX + 128 Then

                    'DAQ packet
                    'Pass off to the DAQ system
                    Me.m_pDAQ.InernalEvent__UDPSafe__RxPacket(SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_DAQ__OFFSET_INDEX,
                                                              ePacketType, u16PayloadLength, u8Payload, u16CRC, True, 0)

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
            Dim btnRequest As New SIL3.ApplicationSupport.ButtonHelper(10, 10, 100, "Request Cal", MyBase.m_pInnerPanel, AddressOf Me.btnRequestCalData__Click)
            btnRequest.ToolTip__Set("Request", "Request a calibration packet")
            Dim btnStream As New SIL3.ApplicationSupport.ButtonHelper(100, "Cal Stream On", AddressOf Me.btnStreamCalData__Click)
            btnStream.Layout__RightOfControl(btnRequest)

            Dim iIndex As Integer = 0
            Dim l0 As New SIL3.ApplicationSupport.LabelHelper("Accel 0 Status Flags")
            l0.Layout__BelowControl(btnRequest)
            Me.m_txtStatusFlags(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0)
            Dim l1 As New SIL3.ApplicationSupport.LabelHelper("X Raw")
            l1.Layout__AboveRightControl(l0, Me.m_txtStatusFlags(iIndex))
            Me.m_txtX_Raw(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_S16(80, l1)
            btnFineX(iIndex) = New SIL3.ApplicationSupport.ButtonHelper(100, "X Fine Zero", AddressOf Me.btnFineX__Click)
            btnFineX(iIndex).Layout__RightOfControl(Me.m_txtX_Raw(iIndex))
            btnFineX(iIndex).Tag = iIndex.ToString
            Dim l2 As New SIL3.ApplicationSupport.LabelHelper("Y Raw")
            l2.Layout__AboveRightControl(l1, btnFineX(iIndex))
            Me.m_txtY_Raw(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_S16(80, l2)
            btnFineY(iIndex) = New SIL3.ApplicationSupport.ButtonHelper(100, "Y Fine Zero", AddressOf Me.btnFineY__Click)
            btnFineY(iIndex).Layout__RightOfControl(Me.m_txtY_Raw(iIndex))
            btnFineY(iIndex).Tag = iIndex.ToString
            Dim l3 As New SIL3.ApplicationSupport.LabelHelper("Z Raw")
            l3.Layout__AboveRightControl(l2, btnFineY(iIndex))
            Me.m_txtZ_Raw(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_S16(80, l3)
            btnFineZ(iIndex) = New SIL3.ApplicationSupport.ButtonHelper(100, "Z Fine Zero", AddressOf Me.btnFineZ__Click)
            btnFineZ(iIndex).Layout__RightOfControl(Me.m_txtZ_Raw(iIndex))
            btnFineZ(iIndex).Tag = iIndex.ToString
            btnAuto(iIndex) = New SIL3.ApplicationSupport.ButtonHelper(100, "Auto Cal", AddressOf Me.btnAutoCal__Click)
            btnAuto(iIndex).Layout__RightOfControl(btnFineZ(iIndex))
            btnAuto(iIndex).Tag = iIndex.ToString

            iIndex += 1
            Dim l10 As New SIL3.ApplicationSupport.LabelHelper("Accel 1 Status Flags", Me.m_txtStatusFlags(iIndex - 1))
            Me.m_txtStatusFlags(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l10)
            Dim l11 As New SIL3.ApplicationSupport.LabelHelper("X Raw")
            l11.Layout__AboveRightControl(l10, Me.m_txtStatusFlags(iIndex))
            Me.m_txtX_Raw(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_S16(80, l11)
            btnFineX(iIndex) = New SIL3.ApplicationSupport.ButtonHelper(100, "X Fine Zero", AddressOf Me.btnFineX__Click)
            btnFineX(iIndex).Layout__RightOfControl(Me.m_txtX_Raw(iIndex))
            btnFineX(iIndex).Tag = iIndex.ToString
            Dim l12 As New SIL3.ApplicationSupport.LabelHelper("Y Raw")
            l12.Layout__AboveRightControl(l11, btnFineX(iIndex))
            Me.m_txtY_Raw(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_S16(80, l12)
            btnFineY(iIndex) = New SIL3.ApplicationSupport.ButtonHelper(100, "Y Fine Zero", AddressOf Me.btnFineY__Click)
            btnFineY(iIndex).Layout__RightOfControl(Me.m_txtY_Raw(iIndex))
            btnFineY(iIndex).Tag = iIndex.ToString
            Dim l13 As New SIL3.ApplicationSupport.LabelHelper("Z Raw")
            l13.Layout__AboveRightControl(l12, btnFineY(iIndex))
            Me.m_txtZ_Raw(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_S16(80, l13)
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

            Dim l100 As New SIL3.ApplicationSupport.LabelHelper("Full Data Streaming")
            l100.Layout__BelowControl(Me.m_txtCount)

            Dim btnRequestFull As New SIL3.ApplicationSupport.ButtonHelper(100, "Request Full", AddressOf Me.btnRequestFullData__Click)
            btnRequestFull.Layout__BelowControl(l100)
            btnRequestFull.ToolTip__Set("Request", "Request a calibration packet")
            Dim btnStreamFull As New SIL3.ApplicationSupport.ButtonHelper(100, "Full Stream On", AddressOf Me.btnStreamFullData__Click)
            btnStreamFull.Layout__RightOfControl(btnRequestFull)

            Dim btnDAQ As New SIL3.ApplicationSupport.ButtonHelper(100, "Enable DAQ", AddressOf Me.btnDAQ__Click)
            btnDAQ.Layout__RightOfControl(btnStreamFull)


            Dim l200(C_NUM_ACCELS - 1, 6 - 1) As SIL3.ApplicationSupport.LabelHelper

            iIndex = 0
            l200(iIndex, 0) = New SIL3.ApplicationSupport.LabelHelper("A:" & iIndex.ToString & " Accel (mm/s^2)")
            l200(iIndex, 0).Layout__BelowControl(btnRequestFull)
            Me.m_txtCalc__CurrentAccel_mmss(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_S32(100, l200(iIndex, 0))

            l200(iIndex, 2) = New SIL3.ApplicationSupport.LabelHelper("A:" & iIndex.ToString & " Veloc (mm/s)")
            l200(iIndex, 2).Layout__AboveRightControl(l200(iIndex, 0), Me.m_txtCalc__CurrentAccel_mmss(iIndex))
            Me.m_txtCalc__CurrentVeloc_mms(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_S32(100, l200(iIndex, 2))

            'l200(iIndex, 3) = New SIL3.ApplicationSupport.LabelHelper("A:" & iIndex.ToString & " Prev Veloc")
            'l200(iIndex, 3).Layout__AboveRightControl(l200(iIndex, 2), Me.m_txtCalc__CurrentVeloc_mms(iIndex))
            'Me.m_txtCalc__PrevVeloc_mms(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_S32(100, l200(iIndex, 3))

            l200(iIndex, 4) = New SIL3.ApplicationSupport.LabelHelper("A:" & iIndex.ToString & " Disp (mm)")
            l200(iIndex, 4).Layout__AboveRightControl(l200(iIndex, 2), Me.m_txtCalc__CurrentVeloc_mms(iIndex))
            Me.m_txtCalc__CurrentDisplacement_mm(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_S32(100, l200(iIndex, 4))

            'l200(iIndex, 5) = New SIL3.ApplicationSupport.LabelHelper("A:" & iIndex.ToString & " Prev Disp.")
            'l200(iIndex, 5).Layout__AboveRightControl(l200(iIndex, 4), Me.m_txtCalc__CurrentDisplacement_mm(iIndex))
            'Me.m_txtCalc__PrevDisplacement_mm(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_S32(100, l200(iIndex, 5))

            iIndex = 1
            l200(iIndex, 0) = New SIL3.ApplicationSupport.LabelHelper("A:" & iIndex.ToString & " Accel (mm/s^2)")
            l200(iIndex, 0).Layout__BelowControl(Me.m_txtCalc__CurrentAccel_mmss(iIndex - 1))
            Me.m_txtCalc__CurrentAccel_mmss(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_S32(100, l200(iIndex, 0))

            l200(iIndex, 2) = New SIL3.ApplicationSupport.LabelHelper("A:" & iIndex.ToString & " Veloc (mm/s)")
            l200(iIndex, 2).Layout__AboveRightControl(l200(iIndex, 0), Me.m_txtCalc__CurrentAccel_mmss(iIndex))
            Me.m_txtCalc__CurrentVeloc_mms(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_S32(100, l200(iIndex, 2))

            'l200(iIndex, 3) = New SIL3.ApplicationSupport.LabelHelper("A:" & iIndex.ToString & " Prev Veloc")
            'l200(iIndex, 3).Layout__AboveRightControl(l200(iIndex, 2), Me.m_txtCalc__CurrentVeloc_mms(iIndex))
            'Me.m_txtCalc__PrevVeloc_mms(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_S32(100, l200(iIndex, 3))

            l200(iIndex, 4) = New SIL3.ApplicationSupport.LabelHelper("A:" & iIndex.ToString & " Disp (mm)")
            l200(iIndex, 4).Layout__AboveRightControl(l200(iIndex, 2), Me.m_txtCalc__CurrentVeloc_mms(iIndex))
            Me.m_txtCalc__CurrentDisplacement_mm(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_S32(100, l200(iIndex, 4))

            'l200(iIndex, 5) = New SIL3.ApplicationSupport.LabelHelper("A:" & iIndex.ToString & " Prev Disp.")
            'l200(iIndex, 5).Layout__AboveRightControl(l200(iIndex, 4), Me.m_txtCalc__CurrentDisplacement_mm(iIndex))
            'Me.m_txtCalc__PrevDisplacement_mm(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_S32(100, l200(iIndex, 5))

            For iIndex = 0 To C_NUM_ACCELS - 1
                Me.m_txtStatusFlags(iIndex).Flags__Add("GENERAL")
                Me.m_txtStatusFlags(iIndex).Flags__Add("SENSOR INDEX NOT FOUND ")
                Me.m_txtStatusFlags(iIndex).Flags__Add("DEVICE NOT WORKING ")
                Me.m_txtStatusFlags(iIndex).Flags__Add("STATUS REGISTER READ FAIL")
                Me.m_txtStatusFlags(iIndex).Flags__Add("INTERRUPT LOST ")
                Me.m_txtStatusFlags(iIndex).Flags__Add("UNABLE TO CALIBRATE ")
                Me.m_txtStatusFlags(iIndex).Flags__Add("RESET CALIBRATION DATA ")
                Me.m_txtStatusFlags(iIndex).Flags__Add("CAL DATA CRC FAULT")
                Me.m_txtStatusFlags(iIndex).Flags__Add("CALIBRATION IN PROGRESS ")
            Next

        End Sub
#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON HELPERS"

        ''' <summary>
        ''' Request some data
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        ''' <remarks></remarks>
        Private Sub btnRequestCalData__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_ACCEL__REQUEST_CAL_DATA,
                                                 0, 0, 0, 0)
        End Sub

        Private Sub btnRequestFullData__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_ACCEL__REQUEST_FULL_DATA,
                                                 0, 0, 0, 0)
        End Sub


        ''' <summary>
        ''' Control the DAQ
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnDAQ__Click(s As Object, e As EventArgs)


            Dim pSB As SIL3.ApplicationSupport.ButtonHelper = CType(s, SIL3.ApplicationSupport.ButtonHelper)

            If pSB.Text = "Enable DAQ" Then

                'clear any types
                Me.m_pDAQ.DAQTypes__Clear()

                'configure the DAQ
                Me.m_pDAQ.DAQTypes__Register(0, 0, 0, DAQ.Top.E_DAQ__DATA_TYPES.DATA_TYPE__U8, "CPU Load", 0)
                Me.m_pDAQ.DAQTypes__Register(0, 0, 1, DAQ.Top.E_DAQ__DATA_TYPES.DATA_TYPE__S16, "A0_X", C_ACCEL_FREQ_HZ)
                Me.m_pDAQ.DAQTypes__Register(0, 0, 2, DAQ.Top.E_DAQ__DATA_TYPES.DATA_TYPE__S16, "A0_Y", C_ACCEL_FREQ_HZ)
                Me.m_pDAQ.DAQTypes__Register(0, 0, 3, DAQ.Top.E_DAQ__DATA_TYPES.DATA_TYPE__S16, "A0_Z", C_ACCEL_FREQ_HZ)
                Me.m_pDAQ.DAQTypes__Register(0, 0, 4, DAQ.Top.E_DAQ__DATA_TYPES.DATA_TYPE__S16, "A1_X", C_ACCEL_FREQ_HZ)
                Me.m_pDAQ.DAQTypes__Register(0, 0, 5, DAQ.Top.E_DAQ__DATA_TYPES.DATA_TYPE__S16, "A1_Y", C_ACCEL_FREQ_HZ)
                Me.m_pDAQ.DAQTypes__Register(0, 0, 6, DAQ.Top.E_DAQ__DATA_TYPES.DATA_TYPE__S16, "A1_Z", C_ACCEL_FREQ_HZ)
                Me.m_pDAQ.DAQTypes__Register(0, 0, 7, DAQ.Top.E_DAQ__DATA_TYPES.DATA_TYPE__S32, "A0_ACCEL", C_ACCEL_FREQ_HZ)
                Me.m_pDAQ.DAQTypes__Register(0, 0, 8, DAQ.Top.E_DAQ__DATA_TYPES.DATA_TYPE__S32, "A0_VELOC", C_ACCEL_FREQ_HZ)
                Me.m_pDAQ.DAQTypes__Register(0, 0, 9, DAQ.Top.E_DAQ__DATA_TYPES.DATA_TYPE__S32, "A0_DISP", C_ACCEL_FREQ_HZ)
                Me.m_pDAQ.DAQTypes__Register(0, 0, 10, DAQ.Top.E_DAQ__DATA_TYPES.DATA_TYPE__S32, "A1_ACCEL", C_ACCEL_FREQ_HZ)
                Me.m_pDAQ.DAQTypes__Register(0, 0, 11, DAQ.Top.E_DAQ__DATA_TYPES.DATA_TYPE__S32, "A1_VELOC", C_ACCEL_FREQ_HZ)
                Me.m_pDAQ.DAQTypes__Register(0, 0, 12, DAQ.Top.E_DAQ__DATA_TYPES.DATA_TYPE__S32, "A1_DISP", C_ACCEL_FREQ_HZ)

                'switch on the DAQ
                Me.m_pDAQ.DAQ__Start(False)

                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__DAQ_ENABLE,
                                                 1, 0, 0, 0)

                pSB.Text = "Disable DAQ"
            Else
                'stopping will also flush
                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__DAQ_ENABLE,
                                                 0, 0, 0, 0)


                'the DAQ will be flished here.

                pSB.Text = "Enable DAQ"
            End If


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
        Private Sub btnStreamCalData__Click(s As Object, e As EventArgs)

            Dim pSB As SIL3.ApplicationSupport.ButtonHelper = CType(s, SIL3.ApplicationSupport.ButtonHelper)

            If pSB.Text = "Cal Stream On" Then
                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__STREAMING_CONTROL,
                                                 1, SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_ACCEL__TX_CAL_DATA, 0, 0)

                pSB.Text = "Cal Stream Off"
            Else
                pSB.Text = "Cal Stream On"
                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__STREAMING_CONTROL,
                                                 0, SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_ACCEL__TX_CAL_DATA, 0, 0)
            End If


        End Sub


        ''' <summary>
        ''' Full data streaming packet
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnStreamFullData__Click(s As Object, e As EventArgs)

            Dim pSB As SIL3.ApplicationSupport.ButtonHelper = CType(s, SIL3.ApplicationSupport.ButtonHelper)

            If pSB.Text = "Full Stream On" Then
                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__STREAMING_CONTROL,
                                                 1, SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_ACCEL__TX_FULL_DATA, 0, 0)

                pSB.Text = "Full Stream Off"
            Else
                pSB.Text = "Full Stream On"
                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__STREAMING_CONTROL,
                                                 0, SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_ACCEL__TX_FULL_DATA, 0, 0)
            End If


        End Sub

#End Region '#Region "BUTTON HELPERS"

    End Class


End Namespace
