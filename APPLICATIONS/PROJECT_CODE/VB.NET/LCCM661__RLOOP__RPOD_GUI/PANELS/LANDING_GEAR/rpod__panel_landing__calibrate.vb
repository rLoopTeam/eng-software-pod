Namespace SIL3.rLoop.rPodControl.Panels.LandingGear

    ''' <summary>
    ''' LGU
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Calibrate
        Inherits SIL3.ApplicationSupport.PanelTemplate

#Region "CONSTANTS"
        Private Const C_NUM_ACTUATORS As Integer = 4
#End Region

#Region "MEMBERS"

        Private m_txtA_ADCRaw(C_NUM_ACTUATORS - 1) As SIL3.ApplicationSupport.TextBoxHelper_U16
        Private m_txtA_Zero(C_NUM_ACTUATORS - 1) As SIL3.ApplicationSupport.TextBoxHelper_S16
        Private m_txtA_Span(C_NUM_ACTUATORS - 1) As SIL3.ApplicationSupport.TextBoxHelper_F32
        Private m_txtA_Extension(C_NUM_ACTUATORS - 1) As SIL3.ApplicationSupport.TextBoxHelper_S32

        Private m_txtA_ExtendLimit(C_NUM_ACTUATORS - 1) As SIL3.ApplicationSupport.TextBoxHelper_U8
        Private m_txtA_RetractLimit(C_NUM_ACTUATORS - 1) As SIL3.ApplicationSupport.TextBoxHelper_U8


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
        Public Event UserEvent__SafeUDP__Tx_X4(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, u32Block3 As UInt32)

#End Region '#Region "EVENTS"

#Region "PANEL LAYOUT"
        ''' <summary>
        ''' Create our layout prior to being shown
        ''' </summary>
        ''' <remarks></remarks>
        Public Overrides Sub LayoutPanel()

            Dim l1 As New SIL3.ApplicationSupport.LabelHelper(10, 10, "Data Streaming", Me.m_pInnerPanel)
            Dim btnStream As New SIL3.ApplicationSupport.ButtonHelper(100, "Stream On", AddressOf Me.btnStreamOn__Click, l1)


            Dim lx(C_NUM_ACTUATORS - 1, 10 - 1) As SIL3.ApplicationSupport.LabelHelper
            For iCounter As Integer = 0 To C_NUM_ACTUATORS - 1

                Dim iIndex As Integer = 0


                If iCounter = 0 Then
                    lx(iCounter, iIndex) = New SIL3.ApplicationSupport.LabelHelper(iCounter.ToString & ": ADC", btnStream)
                Else
                    lx(iCounter, iIndex) = New SIL3.ApplicationSupport.LabelHelper(iCounter.ToString & ": ADC", Me.m_txtA_ADCRaw(iCounter - 1))
                End If

                Me.m_txtA_ADCRaw(iCounter) = New SIL3.ApplicationSupport.TextBoxHelper_U16(100, lx(iCounter, iIndex))
                iIndex += 1


                lx(iCounter, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Zero")
                lx(iCounter, iIndex).Layout__AboveRightControl(lx(iCounter, iIndex - 1), Me.m_txtA_ADCRaw(iCounter))
                Me.m_txtA_Zero(iCounter) = New SIL3.ApplicationSupport.TextBoxHelper_S16(100, lx(iCounter, iIndex))
                iIndex += 1

                lx(iCounter, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Span")
                lx(iCounter, iIndex).Layout__AboveRightControl(lx(iCounter, iIndex - 1), Me.m_txtA_Zero(iCounter))
                Me.m_txtA_Span(iCounter) = New SIL3.ApplicationSupport.TextBoxHelper_F32(100, lx(iCounter, iIndex))
                iIndex += 1

                lx(iCounter, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Height")
                lx(iCounter, iIndex).Layout__AboveRightControl(lx(iCounter, iIndex - 1), Me.m_txtA_Span(iCounter))
                Me.m_txtA_Extension(iCounter) = New SIL3.ApplicationSupport.TextBoxHelper_S32(100, lx(iCounter, iIndex))
                iIndex += 1

                lx(iCounter, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Ext. Lim")
                lx(iCounter, iIndex).Layout__AboveRightControl(lx(iCounter, iIndex - 1), Me.m_txtA_Extension(iCounter))
                Me.m_txtA_ExtendLimit(iCounter) = New SIL3.ApplicationSupport.TextBoxHelper_U8(100, lx(iCounter, iIndex))
                iIndex += 1

                lx(iCounter, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Ret. Lim")
                lx(iCounter, iIndex).Layout__AboveRightControl(lx(iCounter, iIndex - 1), Me.m_txtA_ExtendLimit(iCounter))
                Me.m_txtA_RetractLimit(iCounter) = New SIL3.ApplicationSupport.TextBoxHelper_U8(100, lx(iCounter, iIndex))
                iIndex += 1

            Next


        End Sub
#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON"

        ''' <summary>
        ''' Switch on streaming
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnStreamOn__Click(s As Object, e As EventArgs)
            Dim pSB As SIL3.ApplicationSupport.ButtonHelper = CType(s, SIL3.ApplicationSupport.ButtonHelper)

            If pSB.Text = "Stream On" Then
                pSB.Text = "Stream Off"
                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__LGU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LGU__STREAMING_CONTROL,
                                                 1, SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LGU__TX_ADC_CAL_PACKET, 0, 0)
            Else
                pSB.Text = "Stream On"
                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__LGU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LGU__STREAMING_CONTROL,
                                                 0, SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LGU__TX_ADC_CAL_PACKET, 0, 0)

            End If

        End Sub


#End Region '#Region "BUTTON"

#Region "ETHERNET"
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
                If ePacketType = SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LGU__TX_ADC_CAL_PACKET Then

                    Dim iOffset As Integer = 0


                    For iCounter As Integer = 0 To C_NUM_ACTUATORS - 1

                        iOffset += Me.m_txtA_ADCRaw(iCounter).Value__Update(u8Payload, iOffset)
                        iOffset += Me.m_txtA_Zero(iCounter).Value__Update(u8Payload, iOffset)
                        iOffset += Me.m_txtA_Span(iCounter).Value__Update(u8Payload, iOffset)
                        iOffset += Me.m_txtA_Extension(iCounter).Value__Update(u8Payload, iOffset)
                        iOffset += Me.m_txtA_ExtendLimit(iCounter).Value__Update(u8Payload, iOffset)
                        iOffset += Me.m_txtA_RetractLimit(iCounter).Value__Update(u8Payload, iOffset)

                        'spares
                        iOffset += 16
                    Next

                End If
            End If

        End Sub

#End Region '#Region "ETHERNET"

    End Class


End Namespace
