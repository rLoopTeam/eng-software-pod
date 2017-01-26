Namespace SIL3.rLoop.rPodControl.Panels.FlightControl

    ''' <summary>
    ''' OptoNCDT1320 Interface
    ''' </summary>
    ''' <remarks></remarks>
    Public Class OptoNCDT
        Inherits SIL3.ApplicationSupport.PanelTemplate

#Region "CONSTANTS"
        Private Const C_NUM_LASERS As Integer = 6
#End Region '#Region "CONSTANTS"

#Region "MEMBERS"

        Private m_iRxCount As Integer
        Private m_txtCount As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtCRC As SIL3.ApplicationSupport.TextBoxHelper

        ''' <summary>
        ''' The logging directory
        ''' </summary>
        Private m_sLogDir As String

        Private m_txtModuleFlags As SIL3.ApplicationSupport.TextBoxHelper_FaultFlags

        Private m_txtLaser_Flags() As SIL3.ApplicationSupport.TextBoxHelper_FaultFlags
        Private m_txtLaser_ErrorCount() As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtLaser_Byte1Count() As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtLaser_LaserRaw() As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtLaser_LaserFiltered() As SIL3.ApplicationSupport.TextBoxHelper

        Private m_txtCalValue As SIL3.ApplicationSupport.TextBoxHelper

        Private m_pCSV As SIL3.FileSupport.CSV


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
                If ePacketType = SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LASER_OPTO__TX_LASER_DATA Then

                    Dim iOffset As Integer = 0
                    Dim pU32Module As New SIL3.Numerical.U32(u8Payload, iOffset)
                    iOffset += 4
                    Dim pU32ModuleSpare As New SIL3.Numerical.U32(u8Payload, iOffset)
                    iOffset += 4

                    Dim pU32_LaserFlags(C_NUM_LASERS - 1) As SIL3.Numerical.U32
                    Dim pU32_LaserErrorCount(C_NUM_LASERS - 1) As SIL3.Numerical.U32
                    Dim pU32_LaserByte1(C_NUM_LASERS - 1) As SIL3.Numerical.U32
                    Dim pF32_LaserRaw(C_NUM_LASERS - 1) As SIL3.Numerical.F32
                    Dim pF32_LaserFiltered(C_NUM_LASERS - 1) As SIL3.Numerical.F32
                    Dim pU32_LaserSpare(C_NUM_LASERS - 1) As SIL3.Numerical.U32

                    For iCounter As Integer = 0 To C_NUM_LASERS - 1
                        pU32_LaserFlags(iCounter) = New SIL3.Numerical.U32(u8Payload, iOffset)
                        iOffset += 4
                        pU32_LaserErrorCount(iCounter) = New SIL3.Numerical.U32(u8Payload, iOffset)
                        iOffset += 4
                        pU32_LaserByte1(iCounter) = New SIL3.Numerical.U32(u8Payload, iOffset)
                        iOffset += 4
                        pF32_LaserRaw(iCounter) = New SIL3.Numerical.F32(u8Payload, iOffset)
                        iOffset += 4
                        pF32_LaserFiltered(iCounter) = New SIL3.Numerical.F32(u8Payload, iOffset)
                        iOffset += 4
                        pU32_LaserSpare(iCounter) = New SIL3.Numerical.U32(u8Payload, iOffset)
                        iOffset += 4
                    Next

                    'gui update
                    Me.m_txtModuleFlags.Flags__Update(pU32Module, True)
                    For iCounter As Integer = 0 To C_NUM_LASERS - 1
                        Me.m_txtLaser_Flags(iCounter).Flags__Update(pU32_LaserFlags(iCounter), True)
                        Me.m_txtLaser_ErrorCount(iCounter).Threadsafe__SetText(pU32_LaserErrorCount(iCounter).To_String)
                        Me.m_txtLaser_Byte1Count(iCounter).Threadsafe__SetText(pU32_LaserByte1(iCounter).To_String)
                        Me.m_txtLaser_LaserRaw(iCounter).Threadsafe__SetText(pF32_LaserRaw(iCounter).To__Float32.ToString("0.0000"))
                        Me.m_txtLaser_LaserFiltered(iCounter).Threadsafe__SetText(pF32_LaserFiltered(iCounter).To__Float32.ToString("0.0000"))
                    Next


                    Me.m_iRxCount += 1
                    Me.m_txtCount.Threadsafe__SetText(Me.m_iRxCount.ToString)


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

            Dim l0 As New SIL3.ApplicationSupport.LabelHelper(10, 10, "Module Flags", MyBase.m_pInnerPanel)
            Me.m_txtModuleFlags = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0)

            ReDim Me.m_txtLaser_Flags(C_NUM_LASERS - 1)
            ReDim Me.m_txtLaser_ErrorCount(C_NUM_LASERS - 1)
            ReDim Me.m_txtLaser_Byte1Count(C_NUM_LASERS - 1)
            ReDim Me.m_txtLaser_LaserRaw(C_NUM_LASERS - 1)
            ReDim Me.m_txtLaser_LaserFiltered(C_NUM_LASERS - 1)

            Dim la0(C_NUM_LASERS - 1) As SIL3.ApplicationSupport.LabelHelper
            Dim la1(C_NUM_LASERS - 1) As SIL3.ApplicationSupport.LabelHelper
            Dim la2(C_NUM_LASERS - 1) As SIL3.ApplicationSupport.LabelHelper
            Dim la3(C_NUM_LASERS - 1) As SIL3.ApplicationSupport.LabelHelper
            Dim la4(C_NUM_LASERS - 1) As SIL3.ApplicationSupport.LabelHelper

            For iCounter As Integer = 0 To C_NUM_LASERS - 1


                If iCounter = 0 Then
                    la0(iCounter) = New SIL3.ApplicationSupport.LabelHelper("Laser Flags", Me.m_txtModuleFlags)
                Else
                    la0(iCounter) = New SIL3.ApplicationSupport.LabelHelper("Laser Flags", Me.m_txtLaser_Flags(iCounter - 1))
                End If

                la1(iCounter) = New SIL3.ApplicationSupport.LabelHelper("Error Count")
                la2(iCounter) = New SIL3.ApplicationSupport.LabelHelper("Byte1 Errors")
                la3(iCounter) = New SIL3.ApplicationSupport.LabelHelper("Laser Raw")
                la4(iCounter) = New SIL3.ApplicationSupport.LabelHelper("Laser Filtered")

                Me.m_txtLaser_Flags(iCounter) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, la0(iCounter))
                la1(iCounter).Layout__AboveRightControl(la0(iCounter), Me.m_txtLaser_Flags(iCounter))
                Me.m_txtLaser_ErrorCount(iCounter) = New SIL3.ApplicationSupport.TextBoxHelper(100, la1(iCounter))
                la2(iCounter).Layout__AboveRightControl(la0(iCounter), Me.m_txtLaser_ErrorCount(iCounter))
                Me.m_txtLaser_Byte1Count(iCounter) = New SIL3.ApplicationSupport.TextBoxHelper(100, la2(iCounter))
                la3(iCounter).Layout__AboveRightControl(la0(iCounter), Me.m_txtLaser_Byte1Count(iCounter))
                Me.m_txtLaser_LaserRaw(iCounter) = New SIL3.ApplicationSupport.TextBoxHelper(100, la3(iCounter))
                la4(iCounter).Layout__AboveRightControl(la0(iCounter), Me.m_txtLaser_LaserRaw(iCounter))
                Me.m_txtLaser_LaserFiltered(iCounter) = New SIL3.ApplicationSupport.TextBoxHelper(100, la4(iCounter))


            Next


            Dim l11 As New SIL3.ApplicationSupport.LabelHelper("Rx Count")
            l11.Layout__BelowControl(Me.m_txtLaser_Flags(C_NUM_LASERS - 1))
            Me.m_txtCount = New SIL3.ApplicationSupport.TextBoxHelper(100, l11)

            Dim btnOn As New SIL3.ApplicationSupport.ButtonHelper(100, "Stream On", AddressOf btnStreamOn__Click)
            btnOn.Layout__BelowControl(Me.m_txtCount)


            Dim l22 As New SIL3.ApplicationSupport.LabelHelper("Calibration Value")
            l22.Layout__BelowControl(btnOn)
            Me.m_txtCalValue = New SIL3.ApplicationSupport.TextBoxHelper(100, l22)
            Me.m_txtCalValue.Threadsafe__SetText("0.0")

            Dim btnCal As New SIL3.ApplicationSupport.ButtonHelper(100, "Calibrate", AddressOf btnCal__Click)
            btnCal.Layout__RightOfControl(Me.m_txtCalValue)

        End Sub

#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON HELPERS"

        ''' <summary>
        ''' Height calibration system
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnCal__Click(s As Object, e As EventArgs)

            If MsgBox("Warn: Are you sure you want to set the cal?", MsgBoxStyle.YesNo) = MsgBoxResult.No Then
                Exit Sub
            End If

            Dim pf32 As New SIL3.Numerical.F32(Single.Parse(Me.m_txtCalValue.Text))

            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LASER_OPTO__CAL_LASER_HEIGHT,
                                                 &H11221122, pf32.Union__Uint32, 0, 0)


        End Sub
        Private Sub btnStreamOn__Click(s As Object, e As EventArgs)

            Dim pSB As SIL3.ApplicationSupport.ButtonHelper = CType(s, SIL3.ApplicationSupport.ButtonHelper)
            If pSB.Text = "Stream On" Then
                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__STREAMING_CONTROL,
                                                 1, SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LASER_OPTO__TX_LASER_DATA, 0, 0)

                pSB.Text = "Stream Off"
            Else
                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__STREAMING_CONTROL,
                                                 0, SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LASER_OPTO__TX_LASER_DATA, 0, 0)
                pSB.Text = "Stream On"
            End If


        End Sub

#End Region '#Region "BUTTON HELPERS"

    End Class


End Namespace
