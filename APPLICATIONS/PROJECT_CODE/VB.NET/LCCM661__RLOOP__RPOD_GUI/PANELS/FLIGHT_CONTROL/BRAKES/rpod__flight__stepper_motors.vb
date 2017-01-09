Namespace SIL3.rLoop.rPodControl.Panels.FlightControl

    ''' <summary>
    ''' Stepper Motor Config
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Stepper
        Inherits SIL3.ApplicationSupport.PanelTemplate

#Region "CONSTANTS"
        Private Const C_NUM_MOTORS As Integer = 2
#End Region '#Region "CONSTANTS"

#Region "MEMBERS"

        Private m_iRxCount As Integer
        Private m_txtCount As SIL3.ApplicationSupport.TextBoxHelper

        Private m_txtMotor_MicroSteps() As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtMotor_MaxAngularAccel() As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtMotor_MicronsRev() As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtMotor_MaxRPM() As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtMotor_TimerPeriod() As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtMotor_UpdateFreq() As SIL3.ApplicationSupport.TextBoxHelper

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
            Me.m_sLogDir = Me.m_sLogDir & "STEPPERS\"

            'check our folder
            SIL3.FileSupport.FileHelpers.Folder__CheckWarnMake(Me.m_sLogDir, True)

            'create the log files in prep
            'Me.m_pCSV = New SIL3.FileSupport.CSV(Me.m_sLogDir & "Laser0.csv", ",", False, False)
            'If Me.m_pCSV.File__Exists = False Then
            'End If


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

                'match thepacket
                If ePacketType = SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__TX_MOTOR_PARAM Then

                    Dim iOffset As Integer = 0

                    Dim pU32L_MicrostepRes As New SIL3.Numerical.U32(u8Payload, iOffset)
                    iOffset += 4
                    Dim pS32L_MaxAngularAccel As New SIL3.Numerical.S32(u8Payload, iOffset)
                    iOffset += 4
                    Dim pS32L_MicronsRev As New SIL3.Numerical.S32(u8Payload, iOffset)
                    iOffset += 4
                    Dim pS32L_StepsRev As New SIL3.Numerical.S32(u8Payload, iOffset)
                    iOffset += 4
                    Dim pS32L_MaxAngularVeloc As New SIL3.Numerical.S32(u8Payload, iOffset)
                    iOffset += 4

                    Dim pU32R_MicrostepRes As New SIL3.Numerical.U32(u8Payload, iOffset)
                    iOffset += 4
                    Dim pS32R_MaxAngularAccel As New SIL3.Numerical.S32(u8Payload, iOffset)
                    iOffset += 4
                    Dim pS32R_MicronsRev As New SIL3.Numerical.S32(u8Payload, iOffset)
                    iOffset += 4
                    Dim pS32R_StepsRev As New SIL3.Numerical.S32(u8Payload, iOffset)
                    iOffset += 4
                    Dim pS32R_MaxAngularVeloc As New SIL3.Numerical.S32(u8Payload, iOffset)
                    iOffset += 4

                    Dim u8RTI_Timer As New Numerical.U8(u8Payload, iOffset)
                    iOffset += 1

                    'update the GUI
                    Me.m_txtMotor_MicroSteps(0).Threadsafe__SetText(pU32L_MicrostepRes.To__Int)
                    Me.m_txtMotor_MicroSteps(1).Threadsafe__SetText(pU32R_MicrostepRes.To__Int)
                    Me.m_txtMotor_MaxAngularAccel(0).Threadsafe__SetText(pS32L_MaxAngularAccel.To__Int)
                    Me.m_txtMotor_MaxAngularAccel(1).Threadsafe__SetText(pS32R_MaxAngularAccel.To__Int)
                    Me.m_txtMotor_MicronsRev(0).Threadsafe__SetText(pS32L_MicronsRev.To__Int)
                    Me.m_txtMotor_MicronsRev(1).Threadsafe__SetText(pS32R_MicronsRev.To__Int)
                    Me.m_txtMotor_MicroSteps(0).Threadsafe__SetText(pS32L_StepsRev.To__Int)
                    Me.m_txtMotor_MicroSteps(1).Threadsafe__SetText(pS32R_StepsRev.To__Int)
                    Me.m_txtMotor_MaxRPM(0).Threadsafe__SetText(pS32L_MaxAngularVeloc.To__Int)
                    Me.m_txtMotor_MaxRPM(1).Threadsafe__SetText(pS32R_MaxAngularVeloc.To__Int)

                    Me.m_iRxCount += 1
                    Me.m_txtCount.Threadsafe__SetText(Me.m_iRxCount.ToString)


                End If
            End If

        End Sub

#End Region '#Region "EVENTS"

#Region "PANEL LAYOUT"

        ''' <summary>
        ''' generates a L/R
        ''' </summary>
        ''' <param name="iIndex"></param>
        ''' <returns></returns>
        Private Function Layout__GetBrakeSide(iIndex As Integer) As String
            If iIndex = 0 Then
                Return "L"
            Else
                Return "R"
            End If
        End Function

        ''' <summary>
        ''' Create our layout prior to being shown
        ''' </summary>
        ''' <remarks></remarks>
        Public Overrides Sub LayoutPanel()

            Dim sAxis As String = ""
            ReDim Me.m_txtMotor_MicroSteps(C_NUM_MOTORS - 1)
            ReDim Me.m_txtMotor_MaxAngularAccel(C_NUM_MOTORS - 1)
            ReDim Me.m_txtMotor_MicronsRev(C_NUM_MOTORS - 1)
            ReDim Me.m_txtMotor_MaxRPM(C_NUM_MOTORS - 1)
            ReDim Me.m_txtMotor_TimerPeriod(C_NUM_MOTORS - 1)
            ReDim Me.m_txtMotor_UpdateFreq(C_NUM_MOTORS - 1)
            Dim l0(C_NUM_MOTORS - 1) As SIL3.ApplicationSupport.LabelHelper
            Dim l1(C_NUM_MOTORS - 1) As SIL3.ApplicationSupport.LabelHelper
            Dim l2(C_NUM_MOTORS - 1) As SIL3.ApplicationSupport.LabelHelper
            Dim l3(C_NUM_MOTORS - 1) As SIL3.ApplicationSupport.LabelHelper
            Dim l4(C_NUM_MOTORS - 1) As SIL3.ApplicationSupport.LabelHelper
            Dim l5(C_NUM_MOTORS - 1) As SIL3.ApplicationSupport.LabelHelper

            Dim btnUpdate(C_NUM_MOTORS - 1) As SIL3.ApplicationSupport.ButtonHelper

            For iCounter As Integer = 0 To C_NUM_MOTORS - 1

                Select Case iCounter
                    Case 0
                        sAxis = "L"
                    Case 1
                        sAxis = "R"
                    Case Else
                        sAxis = "?"
                End Select


                If iCounter = 0 Then
                    l0(iCounter) = New SIL3.ApplicationSupport.LabelHelper(10, 10, sAxis & " Microsteps", MyBase.m_pInnerPanel)
                Else
                    l0(iCounter) = New SIL3.ApplicationSupport.LabelHelper(sAxis & " Microsteps")
                    l0(iCounter).Layout__BelowControl(Me.m_txtMotor_MicroSteps(iCounter - 1))
                End If

                Me.m_txtMotor_MicroSteps(iCounter) = New SIL3.ApplicationSupport.TextBoxHelper(80, l0(iCounter))
                Me.m_txtMotor_MicroSteps(iCounter).WaterMarkText = "1"
                Me.m_txtMotor_MicroSteps(iCounter).Tag = iCounter.ToString
                AddHandler Me.m_txtMotor_MicroSteps(iCounter).KeyDown, AddressOf Me.txtMotor_Microsteps__KeyDown

                l1(iCounter) = New SIL3.ApplicationSupport.LabelHelper(sAxis & " Max. Accel")
                l1(iCounter).Layout__AboveRightControl(l0(iCounter), Me.m_txtMotor_MicroSteps(iCounter))
                Me.m_txtMotor_MaxAngularAccel(iCounter) = New SIL3.ApplicationSupport.TextBoxHelper(80, l1(iCounter))
                Me.m_txtMotor_MaxAngularAccel(iCounter).WaterMarkText = "2000"
                Me.m_txtMotor_MaxAngularAccel(iCounter).Tag = iCounter.ToString
                AddHandler Me.m_txtMotor_MaxAngularAccel(iCounter).KeyDown, AddressOf Me.txtMotor_AngularAccel__KeyDown


                l2(iCounter) = New SIL3.ApplicationSupport.LabelHelper(sAxis & " um / rev")
                l2(iCounter).Layout__AboveRightControl(l1(iCounter), Me.m_txtMotor_MaxAngularAccel(iCounter))
                Me.m_txtMotor_MicronsRev(iCounter) = New SIL3.ApplicationSupport.TextBoxHelper(80, l2(iCounter))
                Me.m_txtMotor_MicronsRev(iCounter).WaterMarkText = "1"
                Me.m_txtMotor_MicronsRev(iCounter).Tag = iCounter.ToString
                AddHandler Me.m_txtMotor_MicronsRev(iCounter).KeyDown, AddressOf Me.txtMotor_MicronsRev__KeyDown


                l3(iCounter) = New SIL3.ApplicationSupport.LabelHelper(sAxis & " Max RPM")
                l3(iCounter).Layout__AboveRightControl(l2(iCounter), Me.m_txtMotor_MicronsRev(iCounter))
                Me.m_txtMotor_MaxRPM(iCounter) = New SIL3.ApplicationSupport.TextBoxHelper(80, l3(iCounter))
                Me.m_txtMotor_MaxRPM(iCounter).WaterMarkText = "600"
                Me.m_txtMotor_MaxRPM(iCounter).Tag = iCounter.ToString
                AddHandler Me.m_txtMotor_MaxRPM(iCounter).KeyDown, AddressOf Me.txtMotor_MaxAngularVeloc__KeyDown

                l4(iCounter) = New SIL3.ApplicationSupport.LabelHelper(sAxis & " Timer (uS)")
                l4(iCounter).Layout__AboveRightControl(l3(iCounter), Me.m_txtMotor_MaxRPM(iCounter))
                Me.m_txtMotor_TimerPeriod(iCounter) = New SIL3.ApplicationSupport.TextBoxHelper(80, l4(iCounter))
                Me.m_txtMotor_TimerPeriod(iCounter).WaterMarkText = "?"

                l5(iCounter) = New SIL3.ApplicationSupport.LabelHelper(sAxis & " Update Freq")
                l5(iCounter).Layout__AboveRightControl(l4(iCounter), Me.m_txtMotor_TimerPeriod(iCounter))
                Me.m_txtMotor_UpdateFreq(iCounter) = New SIL3.ApplicationSupport.TextBoxHelper(80, l5(iCounter))
                Me.m_txtMotor_UpdateFreq(iCounter).WaterMarkText = "?"


                'btnUpdate(iCounter) = New SIL3.ApplicationSupport.ButtonHelper(100, "Update", AddressOf Me.btnUpdate__MotorSettings__Click)
                'btnUpdate(iCounter).Tag = iCounter.ToString
                'btnUpdate(iCounter).Layout__RightOfControl(Me.m_txtMotor_UpdateFreq(iCounter))


            Next 'For iCounter As Integer = 0 To 4 - 1

            Dim l100 As New SIL3.ApplicationSupport.LabelHelper("Rx Count")
            l100.Layout__BelowControl(Me.m_txtMotor_MicroSteps(C_NUM_MOTORS - 1))
            Me.m_txtCount = New SIL3.ApplicationSupport.TextBoxHelper(100, l100)

            Dim btnGet As New SIL3.ApplicationSupport.ButtonHelper(100, "Get", AddressOf Me.btnGet__MotorSettings__Click)
            btnGet.Layout__BelowControl(m_txtCount)


        End Sub

#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON HELPERS"

        Private Sub btnGet__MotorSettings__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__REQ_MOTOR_PARAM,
                                                 1, SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__TX_MOTOR_PARAM, 0, 0)
        End Sub

        Private Sub btnUpdate__MotorSettings__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__STREAMING_CONTROL,
                                                 0, SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__TX_DATA, 0, 0)
        End Sub

        Private Sub txtMotor_Microsteps__KeyDown(s As Object, e As KeyEventArgs)

            'get our type
            Dim pT As TextBox = CType(s, TextBox)
            Dim iIndex As Integer = CInt(pT.Tag)

            'handle enter key
            If e.KeyCode = Keys.Enter Then
                Dim u32Value As Int32 = UInt32.Parse(Me.m_txtMotor_MicroSteps(iIndex).Text)

                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__SET_MOTOR_PARAM,
                                                 3, iIndex, u32Value, 0)

            End If

        End Sub


        Private Sub txtMotor_AngularAccel__KeyDown(s As Object, e As KeyEventArgs)

            'get our type
            Dim pT As TextBox = CType(s, TextBox)
            Dim iIndex As Integer = CInt(pT.Tag)

            'handle enter key
            If e.KeyCode = Keys.Enter Then
                Dim s32Value As Int32 = Int32.Parse(Me.m_txtMotor_MaxAngularAccel(iIndex).Text)

                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__SET_MOTOR_PARAM,
                                                 0, iIndex, s32Value, 0)

            End If

        End Sub

        Private Sub txtMotor_MicronsRev__KeyDown(s As Object, e As KeyEventArgs)

            'get our type
            Dim pT As TextBox = CType(s, TextBox)
            Dim iIndex As Integer = CInt(pT.Tag)

            'handle enter key
            If e.KeyCode = Keys.Enter Then
                Dim s32Value As Int32 = Int32.Parse(Me.m_txtMotor_MicronsRev(iIndex).Text)

                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__SET_MOTOR_PARAM,
                                                 1, iIndex, s32Value, 0)

            End If

        End Sub

        Private Sub txtMotor_MaxAngularVeloc__KeyDown(s As Object, e As KeyEventArgs)

            'get our type
            Dim pT As TextBox = CType(s, TextBox)
            Dim iIndex As Integer = CInt(pT.Tag)

            'handle enter key
            If e.KeyCode = Keys.Enter Then
                Dim s32Value As Int32 = Int32.Parse(Me.m_txtMotor_MaxRPM(iIndex).Text)

                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__SET_MOTOR_PARAM,
                                                 2, iIndex, s32Value, 0)

            End If

        End Sub

#End Region '#Region "BUTTON HELPERS"

    End Class


End Namespace
