Namespace SIL3.rLoop.rPodControl.Panels.FlightControl

    ''' <summary>
    ''' Contrast sensor systems
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Contrast
        Inherits SIL3.ApplicationSupport.PanelTemplate

#Region "CONSTANTS"
        Private Const C_NUM_CONTRAST_SENSORS As Integer = 3
#End Region '#Region "CONSTANTS"

#Region "MEMBERS"

        Private m_iRxCount As Integer
        Private m_txtCount As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtStatus As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtCRC As SIL3.ApplicationSupport.TextBoxHelper

        ''' <summary>
        ''' The logging directory
        ''' </summary>
        Private m_sLogDir As String

        ''' <summary>
        ''' Allows us to write CSV logs of the edges
        ''' </summary>
        Private m_pCSV As SIL3.FileSupport.CSV


        ''' <summary>
        ''' Our DAQ Receiver
        ''' </summary>
        Private m_pDAQ As SIL3.DAQ.Top

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
            Me.m_sLogDir = Me.m_sLogDir & "CONTRAST\"

            'check our folder
            SIL3.FileSupport.FileHelpers.Folder__CheckWarnMake(Me.m_sLogDir)

            'create the log files in prep
            Me.m_pCSV = New SIL3.FileSupport.CSV(Me.m_sLogDir & "Laser0.csv", ",", False, False)
            If Me.m_pCSV.File__Exists = False Then
            End If

            'create a DAQ
            'do not pass in any info
            Me.m_pDAQ = New SIL3.DAQ.Top()

            'add the contrast DAQ items
            Me.m_pDAQ.DAQ__Set_LogFilePath(Me.m_sLogDir)

            'cpu load
            Me.m_pDAQ.DAQTypes__Register(0, 0, 0, DAQ.Top.E_DAQ__DATA_TYPES.DATA_TYPE__U8, "CPU Load", 0)
            'rising count
            Me.m_pDAQ.DAQTypes__Register(0, 0, 1, DAQ.Top.E_DAQ__DATA_TYPES.DATA_TYPE__U16, "Rising Edge Count", 0)
            'distance elapsed mm
            Me.m_pDAQ.DAQTypes__Register(0, 0, 2, DAQ.Top.E_DAQ__DATA_TYPES.DATA_TYPE__S32, "Current Accel mm/ss", 0)
            'last stripe distance mm
            Me.m_pDAQ.DAQTypes__Register(0, 0, 3, DAQ.Top.E_DAQ__DATA_TYPES.DATA_TYPE__U32, "Distance Elapsed mm", 0)
            'current velocity mm/s
            Me.m_pDAQ.DAQTypes__Register(0, 0, 4, DAQ.Top.E_DAQ__DATA_TYPES.DATA_TYPE__U32, "Velocity mms", 0)

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

                    Dim iOffset As Integer = 0
                    Dim pU32UpperFaultFlags As New SIL3.Numerical.U32(u8Payload, iOffset)
                    iOffset += 4

                    Dim pU32Spare0 As New SIL3.Numerical.U32(u8Payload, iOffset)
                    iOffset += 4
                    Dim pU32Spare1 As New SIL3.Numerical.U32(u8Payload, iOffset)
                    iOffset += 4
                    Dim pU32Spare2 As New SIL3.Numerical.U32(u8Payload, iOffset)
                    iOffset += 4
                    Dim pU32Spare3 As New SIL3.Numerical.U32(u8Payload, iOffset)
                    iOffset += 4

                    Dim pU32DeviceFaultFlags As New SIL3.Numerical.U32(u8Payload, iOffset)
                    iOffset += 4

                    Dim pU16RisingCount As New SIL3.Numerical.U16(u8Payload, iOffset)
                    iOffset += 2
                    Dim pU16FallingCount As New SIL3.Numerical.U16(u8Payload, iOffset)
                    iOffset += 2
                    Dim pU16MaxStripes As New SIL3.Numerical.U16(u8Payload, iOffset)
                    iOffset += 2

                    'the two timing lists
                    Dim pU64Rise() As SIL3.Numerical.U64
                    ReDim pU64Rise(pU16MaxStripes.To__Int - 1)
                    Dim pU64Fall() As SIL3.Numerical.U64
                    ReDim pU64Fall(pU16MaxStripes.To__Int - 1)


                    'go through the rising list
                    For iCounter As Integer = 0 To pU16MaxStripes.To__Int - 1
                        pU64Rise(iCounter) = New SIL3.Numerical.U64(u8Payload, iOffset)
                        iOffset += 8
                    Next

                    'go through the falling list
                    For iCounter As Integer = 0 To pU16MaxStripes.To__Int - 1
                        pU64Fall(iCounter) = New SIL3.Numerical.U64(u8Payload, iOffset)
                        iOffset += 8
                    Next


                    'to string
                    Dim lS As New List(Of String)

                    lS.Add("Laser 0 - Simulation Run")
                    lS.Add("Date / Time:  " & Now.ToString)
                    lS.Add("-------------------------------------------------------------")
                    lS.Add("Rising Edges: " & pU16RisingCount.To__Int.ToString)
                    lS.Add("Falling Edges: " & pU16FallingCount.To__Int.ToString)
                    lS.Add("Maximum Stripes: " & pU16MaxStripes.To__Int.ToString)
                    lS.Add("-------------------------------------------------------------")
                    lS.Add("Rising Edge Index,CPU Clock,Elapsed Time (x20 ns),Elapsed Time (s)")

                    For iCounter As Integer = 0 To pU16MaxStripes.To__Int - 1
                        Dim sTemp As String = iCounter.ToString("00") & ","
                        sTemp = sTemp & pU64Rise(iCounter).To__Uint64.ToString & ","

                        If iCounter = 0 Then
                            Dim s64Elapsed As Int64 = 0
                            sTemp = sTemp & s64Elapsed.ToString & ","
                            sTemp = sTemp & s64Elapsed.ToString
                        Else
                            Dim s64Elapsed As Int64 = pU64Rise(iCounter).To__Uint64
                            s64Elapsed = s64Elapsed - pU64Rise(iCounter - 1).To__Uint64
                            sTemp = sTemp & s64Elapsed.ToString & ","

                            Dim f64 As Double = s64Elapsed
                            'convert to ns
                            f64 *= 20.0
                            'convert to seconds
                            f64 /= 1000000000.0
                            sTemp = sTemp & f64.ToString("0.000000")
                        End If

                        lS.Add(sTemp)
                    Next


                    lS.Add("-------------------------------------------------------------")
                    lS.Add("Falling Edge Index,CPU Clock,Elapsed Time (x20 ns),Elapsed Time (s)")
                    For iCounter As Integer = 0 To pU16MaxStripes.To__Int - 1
                        Dim sTemp As String = iCounter.ToString("00") & ","
                        sTemp = sTemp & pU64Fall(iCounter).To__Uint64.ToString & ","

                        If iCounter = 0 Then
                            Dim s64Elapsed As Int64 = 0
                            sTemp = sTemp & s64Elapsed.ToString & ","
                            sTemp = sTemp & s64Elapsed.ToString
                        Else
                            Dim s64Elapsed As Int64 = pU64Fall(iCounter).To__Uint64
                            s64Elapsed = s64Elapsed - pU64Fall(iCounter - 1).To__Uint64
                            sTemp = sTemp & s64Elapsed.ToString & ","

                            Dim f64 As Double = s64Elapsed
                            'convert to ns
                            f64 *= 20.0
                            'convert to seconds
                            f64 /= 1000000000.0
                            sTemp = sTemp & f64.ToString("0.000000")
                        End If

                        lS.Add(sTemp)
                    Next

                    SIL3.FileSupport.FileHelpers.File__WriteLines(Me.m_sLogDir & "Laser0.txt", lS)


                    Me.m_iRxCount += 1
                    Me.m_txtCount.Threadsafe__SetText(Me.m_iRxCount.ToString)


                ElseIf ePacketType >= SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_DAQ__OFFSET_INDEX And ePacketType <= SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_DAQ__OFFSET_INDEX + 128 Then

                    'DAQ packet
                    'Pass off to the DAQ system
                    Me.m_pDAQ.InernalEvent__UDPSafe__RxPacket(SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_DAQ__OFFSET_INDEX,
                                                              ePacketType, u16PayloadLength, u8Payload, u16CRC, True, 0)

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

            Dim l0 As New SIL3.ApplicationSupport.LabelHelper(10, 10, "Contrast Laser Edge Data", MyBase.m_pInnerPanel)
            Dim btnRL0 As New SIL3.ApplicationSupport.ButtonHelper(100, "Req. Laser 0", AddressOf btnRequest_L0__Click)
            btnRL0.Layout__BelowControl(l0)

            Dim btnEnableDAQ As New SIL3.ApplicationSupport.ButtonHelper(100, "Enable DAQ", AddressOf btnEnableDAQ__Click)
            btnEnableDAQ.Layout__RightOfControl(btnRL0)
            btnEnableDAQ.ToolTip__Set("Enable DAQ", "You must enable this BEFORE starting a FPGA sim otherwise the DAQ won't log")

            Dim btnBurst As New SIL3.ApplicationSupport.ButtonHelper(100, "Burst DAQ", AddressOf btnBurstDAQ__Click)
            btnBurst.Layout__RightOfControl(btnEnableDAQ)


            Dim btnRL1 As New SIL3.ApplicationSupport.ButtonHelper(100, "Req. Laser 1", AddressOf btnRequest_L1__Click)
            btnRL1.Layout__BelowControl(btnRL0)
            Dim btnRL2 As New SIL3.ApplicationSupport.ButtonHelper(100, "Req. Laser 2", AddressOf btnRequest_L2__Click)
            btnRL2.Layout__BelowControl(btnRL1)

            Dim l11 As New SIL3.ApplicationSupport.LabelHelper("Rx Count")
            l11.Layout__BelowControl(btnRL2)
            Me.m_txtCount = New SIL3.ApplicationSupport.TextBoxHelper(100, l11)

        End Sub

#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON HELPERS"

        Private Sub btnEnableDAQ__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__DAQ_ENABLE,
                                                 1, 0, 0, 0)
        End Sub

        Private Sub btnBurstDAQ__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__DAQ_FLUSH,
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
