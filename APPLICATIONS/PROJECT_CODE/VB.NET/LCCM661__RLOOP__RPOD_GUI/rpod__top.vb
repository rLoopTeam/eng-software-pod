Namespace SIL3.rLoop.rPodControl

    ''' <summary>
    ''' Toolbox for rPod Controller Top level
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Toolbox

#Region "CONSTANTS"

#End Region '#Region "CONSTANTS"

#Region "MEMBERS"

        ''' <summary>
        ''' A UDP packet
        ''' </summary>
        Private Structure _strUDP
            Dim eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS
            Dim u16PacketType As UInt16
            Dim u16PayloadLength As LAPP188__RLOOP__LIB.SIL3.Numerical.U16
            Dim u8Payload() As Byte
            Dim u16CRC As LAPP188__RLOOP__LIB.SIL3.Numerical.U16
            Dim bCRC_OK As Byte
            Dim u32Sequence As UInt32
        End Structure


        ''' <summary>
        ''' The explorer bar
        ''' </summary>
        ''' <remarks></remarks>
        Private m_pExplorer As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ExplorerBarHelper

        ''' <summary>
        ''' The settings panel
        ''' </summary>
        ''' <remarks></remarks>
        Private m_pnlSettings As SIL3.rLoop.rPodControl.Panels.Settings.Top

        ''' <summary>
        ''' The Flight Control Interface
        ''' </summary>
        ''' <remarks></remarks>
        Private m_pnlFlightControl As SIL3.rLoop.rPodControl.Panels.FlightControl.Top

        ''' <summary>
        ''' AuxProp top level
        ''' </summary>
        Private m_pnlAuxProp As SIL3.rLoop.rPodControl.Panels.AuxProp.Top

        ''' <summary>
        ''' Hover Engine Thermal Management System
        ''' </summary>
        Private m_pnlHETherm As SIL3.rLoop.rPodControl.Panels.HETherm.Top

        ''' <summary>
        ''' Gimbal Unit
        ''' </summary>
        Private m_pnlGimbal As SIL3.rLoop.rPodControl.Panels.Gimbal.Top

        ''' <summary>
        ''' Landing Gear Interface
        ''' </summary>
        Private m_pnlLandingGear As SIL3.rLoop.rPodControl.Panels.LandingGear.Top

        ''' <summary>
        ''' Xilinx simulation module
        ''' </summary>
        Private m_pnlXilinxSim As SIL3.rLoop.rPodControl.Panels.XilinxSim.Top

        ''' <summary>
        ''' The ethernet interface
        ''' </summary>
        Private m_pEth As SIL3.rLoop.rPodControl.Ethernet.EthInterface

        ''' <summary>
        ''' The lower status strip
        ''' </summary>
        ''' <remarks></remarks>
        Private m_pSS As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.StatusStripHelper

        ''' <summary>
        ''' Dequeue our data
        ''' </summary>
        Private pDeQThread_Data As System.Threading.Thread

        ''' <summary>
        ''' The data capture queue
        ''' </summary>
        Private m_pQueue As Concurrent.ConcurrentQueue(Of _strUDP)

        ''' <summary>
        ''' Term the thread?
        ''' </summary>
        Private m_bTerminate As Boolean

        Private m_iRx_FCU As Integer
        Private m_iTx_FCU As Integer

#End Region '#Region "MEMBERS"

#Region "NEW"


        ''' <summary>
        ''' create a new instance
        ''' </summary>
        ''' <param name="pForm"></param>
        ''' <remarks></remarks>
        Public Sub New(ByRef pForm As Form)

            'create the form
            Me.Layout(pForm)

            Me.m_pEth = New SIL3.rLoop.rPodControl.Ethernet.EthInterface()

            'add our ports
            'http://confluence.rloop.org/display/SD/Communications

            If MsgBox("Do you want to run this in loopback on 127.0.0.1?" & Environment.NewLine & "Answering NO will run on 192.168.x.x", MsgBoxStyle.YesNo) = MsgBoxResult.Yes Then
                Me.m_pEth.Port__Add("127.0.0.1", 9531, Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU)
                Me.m_pEth.Port__Add("127.0.0.1", 9615, Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__APU)
                Me.m_pEth.Port__Add("127.0.0.1", 9608, Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__HETHERM)
                Me.m_pEth.Port__Add("127.0.0.1", 9130, Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__GIMBAL)
                Me.m_pEth.Port__Add("127.0.0.1", 9548, Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__LGU)
                Me.m_pEth.Port__Add("127.0.0.1", 3000, Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU_SPACEX_DIAG)
                Me.m_pEth.Port__Add("127.0.0.1", 9170, Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__XILINX_SIM)
            Else

                Dim sP As String = "192.168.0."
                If MsgBox("Do you want to run this on 192.168.1.x" & Environment.NewLine & "Answering no it will be 192.168.0.x", MsgBoxStyle.YesNo) = MsgBoxResult.Yes Then
                    sP = "192.168.1."
                End If

                Me.m_pEth.Port__Add(sP & "100", 9531, Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU)
                Me.m_pEth.Port__Add(sP & "140", 9615, Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__APU)
                Me.m_pEth.Port__Add(sP & "141", 9608, Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__HETHERM)
                Me.m_pEth.Port__Add(sP & "130", 9130, Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__GIMBAL)
                Me.m_pEth.Port__Add(sP & "120", 9548, Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__LGU)
                Me.m_pEth.Port__Add(sP & "100", 3000, Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU_SPACEX_DIAG)
                Me.m_pEth.Port__Add(sP & "170", 9170, Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__XILINX_SIM)

            End If


            'rx handler
            AddHandler Me.m_pEth.UserEvent__UDPSafe__RxPacketB, AddressOf Me.InternalEvent__UDPSafe__RxPacketB
            AddHandler Me.m_pEth.UserEvent__RxPacketA, AddressOf Me.InternalEvent__RxPacketA

            'create the QUEUE
            Me.m_pQueue = New Concurrent.ConcurrentQueue(Of _strUDP)


            Me.pDeQThread_Data = New System.Threading.Thread(AddressOf Me.ThreadRun_DeQueue)
            Me.pDeQThread_Data.Name = "RPOD__DATA_DEQUEUE"
            Me.pDeQThread_Data.Start()


        End Sub

        ''' <summary>
        ''' Close the application
        ''' </summary>
        ''' <remarks></remarks>
        Public Sub Destroy()
            Me.m_bTerminate = True
            'Kill the eth interface
            Me.m_pEth.Destroy()
            Me.pDeQThread_Data.Abort()
        End Sub

#End Region '#Region "NEW"

#Region "LAYOUT"
        ''' <summary>
        ''' Create the layout.
        ''' </summary>
        ''' <remarks></remarks>
        Private Sub Layout(ByRef pForm As Form)


            'setup the form
            pForm.Text = "rPod Control Toolbox (Build" & My.Application.Info.Version.ToString & ")"
            'pF.BackColor = Color.White
            pForm.WindowState = FormWindowState.Maximized

            'setup the explorer bar
            Me.m_pExplorer = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ExplorerBarHelper(Nothing)

            'Me.m_pExplorer.Bar__ImageList_Add("bullet_square_green.png")
            'Me.m_pExplorer.Bar__ImageList_Add("bullet_square_yellow.png")
            'Me.m_pExplorer.Bar__ImageList_Add("bullet_square_red.png")

            Me.m_pnlSettings = New SIL3.rLoop.rPodControl.Panels.Settings.Top(pForm, Me.m_pExplorer)



            Me.m_pnlFlightControl = New SIL3.rLoop.rPodControl.Panels.FlightControl.Top(pForm, Me.m_pExplorer, Me.m_pnlSettings.Get__DataLogDir)
            AddHandler Me.m_pnlFlightControl.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4_FCU
            AddHandler Me.m_pnlFlightControl.UserEvent__SafeUDP__Tx_X3_Array, AddressOf Me.InternalEvent__SafeUDP__Tx_X3_Array

            Me.m_pnlLandingGear = New SIL3.rLoop.rPodControl.Panels.LandingGear.Top(pForm, Me.m_pExplorer)
            AddHandler Me.m_pnlLandingGear.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4
            Me.m_pnlAuxProp = New SIL3.rLoop.rPodControl.Panels.AuxProp.Top(pForm, Me.m_pExplorer)
            AddHandler Me.m_pnlAuxProp.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4
            Me.m_pnlHETherm = New SIL3.rLoop.rPodControl.Panels.HETherm.Top(pForm, Me.m_pExplorer)
            AddHandler Me.m_pnlHETherm.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4
            Me.m_pnlGimbal = New SIL3.rLoop.rPodControl.Panels.Gimbal.Top(pForm, Me.m_pExplorer)
            AddHandler Me.m_pnlGimbal.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4

            Me.m_pnlXilinxSim = New SIL3.rLoop.rPodControl.Panels.XilinxSim.Top(pForm, Me.m_pExplorer)
            AddHandler Me.m_pnlXilinxSim.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4

            'add to our form (do this at the end to prevent window overlapping)
            Me.m_pExplorer.Set__Form(pForm)
            AddHandler Me.m_pExplorer.LinkClick, AddressOf Me.LinkBar_LinkClick

            'Create the status strip helper.
            Me.m_pSS = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.StatusStripHelper(pForm)

            'Make some panels
            Me.m_pSS.Panel__Add("FCU: Rx: 00000, RxQ: 00000, Tx: 00000")
            Me.m_pSS.Panel__Add("LGU: Rx: 00000, RxQ: 00000, Tx: 00000")
            Me.m_pSS.Panel__Add("APU: Rx: 00000, RxQ: 00000, Tx: 00000")
            Me.m_pSS.Panel__Add("GCU: Rx: 00000, RxQ: 00000, Tx: 00000")
            Me.m_pSS.Panel__Add("HET: Rx: 00000, RxQ: 00000, Tx: 00000")

        End Sub

#End Region '#Region "LAYOUT"

#Region "EXPLORER BAR"
        ''' <summary>
        ''' Called when a link is clicked
        ''' </summary>
        ''' <param name="sText"></param>
        ''' <remarks></remarks>
        Private Sub LinkBar_LinkClick(ByVal sText As String)
            Me.m_pnlSettings.Panel__HideShow(sText)
            Me.m_pnlFlightControl.Panel__HideShow(sText)
            Me.m_pnlLandingGear.Panel__HideShow(sText)
            Me.m_pnlGimbal.Panel__HideShow(sText)
            Me.m_pnlAuxProp.Panel__HideShow(sText)
            Me.m_pnlHETherm.Panel__HideShow(sText)
            Me.m_pnlXilinxSim.Panel__HideShow(sText)
        End Sub
#End Region '#Region "EXPLORER BAR"

#Region "ETHERNET TX"

        ''' <summary>
        ''' Some lower module wants to transmit to to the eth
        ''' </summary>
        ''' <param name="eEndpoint"></param>
        ''' <param name="u16Type"></param>
        ''' <param name="u32Block0"></param>
        ''' <param name="u32Block1"></param>
        ''' <param name="u32Block2"></param>
        ''' <param name="u32Block3"></param>
        Public Sub InternalEvent__SafeUDP__Tx_X4(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, u32Block3 As UInt32)
            Me.m_pEth.User__SafeUDP__Tx_X4(eEndpoint, u16Type, u32Block0, u32Block1, u32Block2, u32Block3)
        End Sub

        Public Sub InternalEvent__SafeUDP__Tx_X4_FCU(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, u32Block3 As UInt32)
            Me.m_iTx_FCU += 1
            Me.m_pEth.User__SafeUDP__Tx_X4(eEndpoint, u16Type, u32Block0, u32Block1, u32Block2, u32Block3)
        End Sub


        ''' <summary>
        ''' 3x Blocks and a array
        ''' </summary>
        ''' <param name="eEndpoint"></param>
        ''' <param name="u16Type"></param>
        ''' <param name="u32Block0"></param>
        ''' <param name="u32Block1"></param>
        ''' <param name="u32Block2"></param>
        ''' <param name="pu8Array"></param>
        ''' <param name="iArrayLength"></param>
        Private Sub InternalEvent__SafeUDP__Tx_X3_Array(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, pu8Array() As Byte, iArrayLength As Integer)
            Me.m_pEth.User__SafeUDP__Tx_X3_Array(eEndpoint, u16Type, u32Block0, u32Block1, u32Block2, pu8Array, iArrayLength)

        End Sub

#End Region '#Region "ETHERNET TX"

#Region "ETHERNET RX"
        ''' <summary>
        ''' New Packet Rx'd
        ''' </summary>
        ''' <param name="eEndpoint"></param>
        ''' <param name="u16PacketType"></param>
        ''' <param name="u16PayloadLength"></param>
        ''' <param name="u8Payload"></param>
        ''' <param name="u16CRC"></param>
        ''' <param name="bCRC_OK"></param>
        ''' <param name="u32Sequence"></param>
        Private Sub InternalEvent__UDPSafe__RxPacketB(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16PacketType As UInt16, ByVal u16PayloadLength As LAPP188__RLOOP__LIB.SIL3.Numerical.U16, ByRef u8Payload() As Byte, ByVal u16CRC As LAPP188__RLOOP__LIB.SIL3.Numerical.U16, ByVal bCRC_OK As Boolean, ByVal u32Sequence As UInt32)

            Dim pX As _strUDP

            pX.eEndpoint = eEndpoint
            pX.u16PacketType = u16PacketType
            pX.u16PayloadLength = u16PayloadLength

            ReDim pX.u8Payload(u8Payload.Length - 1)
            For iCounter As Integer = 0 To u8Payload.Length - 1
                pX.u8Payload(iCounter) = u8Payload(iCounter)
            Next
            pX.u16CRC = u16CRC
            pX.bCRC_OK = bCRC_OK
            pX.u32Sequence = u32Sequence

            Me.m_pQueue.Enqueue(pX)

        End Sub

        ''' <summary>
        ''' Raw packet
        ''' </summary>
        ''' <param name="eEndpoint"></param>
        ''' <param name="u8Array"></param>
        ''' <param name="iLength"></param>
        Private Sub InternalEvent__RxPacketA(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u8Array() As Byte, iLength As Integer)
            Select Case eEndpoint
                Case Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU_SPACEX_DIAG
                    Me.m_pnlFlightControl.InternalEvent__RxPacketA(u8Array, iLength)
            End Select
        End Sub

#End Region '#Region "ETHERNET RX"

#Region "QUEUE"
        ''' <summary>
        ''' Gets the count of items in the queue
        ''' </summary>
        ''' <returns></returns>
        Public Function Queue__GetCount() As Integer
            Return Me.m_pQueue.Count
        End Function

        ''' <summary>
        ''' Dequeue our data
        ''' </summary>
        Private Sub ThreadRun_DeQueue()

            While True

                If Me.m_bTerminate = True Then
                    Exit Sub
                End If

                Dim pUDP As _strUDP = Nothing

                'see if we have anything queued
                If Me.m_pQueue.TryDequeue(pUDP) = True Then


                    Select Case pUDP.eEndpoint
                        Case Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__XILINX_SIM
                            Me.m_pnlXilinxSim.InternalEvent__UDPSafe__RxPacketB(pUDP.u16PacketType, pUDP.u16PayloadLength, pUDP.u8Payload, pUDP.u16CRC, pUDP.bCRC_OK, pUDP.u32Sequence)

                        Case Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU
                            Me.m_pnlFlightControl.InternalEvent__UDPSafe__RxPacketB(pUDP.u16PacketType, pUDP.u16PayloadLength, pUDP.u8Payload, pUDP.u16CRC, pUDP.bCRC_OK, pUDP.u32Sequence)
                            Me.m_iRx_FCU += 1
                            Me.m_pSS.Panel__SetText(0, "FCU: Rx: " & Me.m_iRx_FCU.ToString("00000") & ", RxQ: " & Me.m_pQueue.Count.ToString("00000") & ", Tx: " & Me.m_iTx_FCU.ToString("00000"))

                        Case Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__LGU
                            Me.m_pnlLandingGear.InternalEvent__UDPSafe__RxPacketB(pUDP.u16PacketType, pUDP.u16PayloadLength, pUDP.u8Payload, pUDP.u16CRC, pUDP.bCRC_OK, pUDP.u32Sequence)

                        Case Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__HETHERM
                            Me.m_pnlHETherm.InternalEvent__UDPSafe__RxPacketB(pUDP.u16PacketType, pUDP.u16PayloadLength, pUDP.u8Payload, pUDP.u16CRC, pUDP.bCRC_OK, pUDP.u32Sequence)

                        Case Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__APU
                            Me.m_pnlAuxProp.InternalEvent__UDPSafe__RxPacketB(pUDP.u16PacketType, pUDP.u16PayloadLength, pUDP.u8Payload, pUDP.u16CRC, pUDP.bCRC_OK, pUDP.u32Sequence)

                    End Select

                End If

                System.Threading.Thread.Sleep(2)

            End While
        End Sub

#End Region '#Region "QUEUE"

    End Class

End Namespace