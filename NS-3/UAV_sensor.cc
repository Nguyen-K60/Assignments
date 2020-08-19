/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 University of Washington
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */



#include "ns3/core-module.h"
#include "ns3/mobility-module.h"
#include "ns3/wifi-module.h"
#include "ns3/internet-module.h"
#include "ns3/olsr-helper.h"
#include <string>
using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("WifiSimpleAdhocGrid");

void ReceivePacket (Ptr<Socket> socket)
{
  Ptr<Packet> packet = socket->Recv(); // nhận gói tin
  int size = packet->GetSize (); //kích thước gói tin
  uint8_t *buffer = new uint8_t[size];
  packet->CopyData(buffer, size); // copy nội dung gói tin vào buffer
  std::string str = std::string((char*)buffer);// chuyến sang kiểu string để tiện cho việc đọc nội dung
  // đọc nội dung gói tin
  // 3 ký tự đầu biểu diễn id nút gửi
  // 4 ký tự đầu biểu diễn x
  // 4 ký tự tiếp theo biêủ diễn y
  // 4 ký tự cuối biểu diễn z
  NS_LOG_UNCOND ("Received one packet: "<<str);
  // hoàn thành 4 lệnh dưới đây để đọc giá trị của id nút gửi, x, y, z từ biến str, sau đó hiển thị giá trị này ra màn hình
  // int id = ;
  // int x = ;
  // int y = ;
  // int z = ;
  //std::cout<<"id = "<<id<<", x = "<<x<<", y = "<<", z = "<<z<<std::endl;
  
}
// gửi id và vị trí hiện tại cho nút đích
void GenerateTraffic (Ptr<Socket> socket, uint32_t pktSize,
                             uint32_t pktCount, Time pktInterval )
{
  if (pktCount > 0)
  {
    Ptr<Node> sender = socket->GetNode(); // nút gửi
    int id = sender->GetId(); // id nút gửi, mỗi nút có 1 id riêng
    Vector pos = sender->GetObject<MobilityModel>()->GetPosition(); // lấy vị trí nút gửi
    int x = (int)pos.x;
    int y = (int)pos.y;
    int z = (int)pos.z;
    std::ostringstream message;
    // để bên nhận đọc được nội dung, cần định dạng gói tin
    // 3 ký tự đầu biểu diễn id nút gửi
    // 4 ký tự tiếp biểu diễn toạ độ x
    // 4 ký tự tiếp theo biểu diễn toạ độ y
    // 4 ký tự cuối biểu diễn tọa độ z
    if(id < 10)
    {
      message<<"00"<<id;
    }
    else if(id < 100)
    {
      message<<"0"<<id;
    }
    else
    {
      message<<id;
    }
    if(x < 10)
    {
      message<<"000"<<x;
    }
    else if(x < 100)
    {
      message<<"00"<<x;
    }
    else if(x < 1000)
    {
     message <<"0"<<x;
    }
    else
    {
      message<<x;
    }
    if(y < 10)
    {
      message<<"000"<<y;
    }
    else if(y < 100)
    {
      message<<"00"<<y;
    }
    else if(y < 1000)
    {
      message <<"0"<<y;
    }
    else
    {
      message<<y;
    }
    if(z < 10)
    {
      message<<"000"<<z;
    }
    else if(z < 100)
    {
      message<<"00"<<z;
    }
    else if(z < 1000)
    {
      message <<"0"<<z;
    }
    else
    {
      message<<z;
    }
    Ptr<Packet> packet = Create<Packet>((uint8_t*) message.str().c_str(), pktSize);
    socket->Send(packet);
    Simulator::Schedule (pktInterval, &GenerateTraffic,
                           socket, pktSize,pktCount - 1, pktInterval);
  }
  else
  {
    socket->Close ();
  }
}

int main (int argc, char *argv[])
{
  double distance = 500;  // m
  uint32_t packetSize = 1000; // bytes
  uint32_t numPackets = 1;
  uint32_t numSensors = 25;  // tổng số sensor
  double interval = 1.0; // seconds
  // Convert to time object
  Time interPacketInterval = Seconds (interval);
  NodeContainer sensor; // Container chứa những đối tượng cùng loại, NodeContainer là Container chứa nhiều Node
  sensor.Create (numSensors); // tạo nút
  // Đặt vị trí cho các nút sensor theo dạng lưới, kích thước mắt lưới là 500 m x 500 m
  // Vị trí các sensors như sau:
  // n20  n21  n22  n23  n24
  // n15  n16  n17  n18  n19
  // n10  n11  n12  n13  n14
  // n5   n6   n7   n8   n9
  // n0   n1   n2   n3   n4
  MobilityHelper mobility;
  mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
                                 "MinX", DoubleValue (0.0), // vị trí bắt đầu
                                 "MinY", DoubleValue (0.0), //   
                                 "LayoutType", StringValue ("RowFirst"), // sắp xếp theo hàng 
                                 "GridWidth", UintegerValue (5), // mỗi hàng 5 nút, nút thứ 6 sẽ xếp ở hàng tiếp theo
                                 "DeltaX", DoubleValue (distance), // khoảng cách giữa 2 nút liên tiếp trong 1 hàng
                                 "DeltaY", DoubleValue (distance) // khoảng các giữa 2 nút liên tiếp trong 1 cột
                                 );
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel"); // vị trí cố định, không được đặt vận tốc cho nút
  mobility.Install (sensor);
  // đặt vị trí cho UAV.
  Ptr<Node> UAV = CreateObject<Node>();
  mobility.SetMobilityModel ("ns3::ConstantVelocityMobilityModel"); // vận tốc cố định
  mobility.Install(UAV);
  UAV->GetObject<MobilityModel>()->SetPosition(Vector(2500, 0, 100));

  NodeContainer allNodes(sensor, UAV);
  // thiết lập WIFI cho các nút, tạm thời không cần đọc quá kỹ về phần này
  std::string phyMode ("DsssRate1Mbps");
  // disable fragmentation for frames below 2200 bytes
  Config::SetDefault ("ns3::WifiRemoteStationManager::FragmentationThreshold", StringValue ("2200"));
  // turn off RTS/CTS for frames below 2200 bytes
  Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold", StringValue ("2200"));
  // Fix non-unicast data rate to be the same as that of unicast
  Config::SetDefault ("ns3::WifiRemoteStationManager::NonUnicastMode",
                      StringValue (phyMode));
  WifiHelper wifi;
  // lớp vật lý (Phy)
  YansWifiPhyHelper wifiPhy =  YansWifiPhyHelper::Default (); //
  // set it to zero; otherwise, gain will be added
  wifiPhy.Set ("RxGain", DoubleValue (-10) ); // tăng ích bên nhận
  // ns-3 supports RadioTap and Prism tracing extensions for 802.11b
  wifiPhy.SetPcapDataLinkType (YansWifiPhyHelper::DLT_IEEE802_11_RADIO); // theo dõi gói tin
  // kênh truyền (channel)
  YansWifiChannelHelper wifiChannel;
  wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
  wifiChannel.AddPropagationLoss ("ns3::FriisPropagationLossModel");
  wifiPhy.SetChannel (wifiChannel.Create ());
  //lớp MAC
  // Add an upper mac and disable rate control
  WifiMacHelper wifiMac;
  wifi.SetStandard (WIFI_PHY_STANDARD_80211b);
  wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
                                "DataMode",StringValue (phyMode),
                                "ControlMode",StringValue (phyMode));
  // Set it to adhoc mode
  // adhoc tức là các nút trong mạng có vai trò bình đẳng, trao đổi trực tiếp với nhau, không cần thông qua nút trung gian
  wifiMac.SetType ("ns3::AdhocWifiMac");
  NetDeviceContainer devices = wifi.Install (wifiPhy, wifiMac, allNodes);
  // thiết lập giao thức định tuyến OLSR, tạm thời không quan tâm đến hoạt động của giao thức này
  // Enable OLSR
  OlsrHelper olsr;
  Ipv4StaticRoutingHelper staticRouting;

  Ipv4ListRoutingHelper list;
  list.Add (staticRouting, 0);
  list.Add (olsr, 10);
  // cài internetstack cho các nút
  // internetstack bao gồm một số protocol, chi tiết xem phương thức Install(Ptr<Node> node) tại file src/internet/helper/internet-stack-helper.cc
  InternetStackHelper internet;
  internet.SetRoutingHelper (list); // has effect on the next Install ()
  internet.Install (allNodes);
  // đánh địa chỉ IP 
  Ipv4AddressHelper ipv4;
  NS_LOG_INFO ("Assign IP Addresses.");
  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer i = ipv4.Assign (devices);
  // gói tin truyền đi cần phải có socket
  // socket = địa chỉ IP + cổng
  // thiết lập socket tại bên nhận (uav)
  TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory"); // loại socket
  Ptr<Socket> recvSink = Socket::CreateSocket (UAV, tid); // tạo socket ứng với nút nhận
  InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 80); // tất cả địa chỉ ipv4 có cổng = 80, có thể thay 80 bằng con số khác.
  recvSink->Bind (local);//        sinkNode nhận tất cả gói tin gửi đến cổng 80                                         
  recvSink->SetRecvCallback (MakeCallback (&ReceivePacket)); // khi nhận được gói tin thì sẽ gọi hàm ReceivePacket()
  // thiết lập socket bên gửi
  // tất cả sensor gửi tin cho UAV
  Ptr<Socket> source[numSensors];
  Ipv4Address ip = UAV->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal(); // địa chỉ ip của nút nhận
  InetSocketAddress remote = InetSocketAddress (ip , 80); // địa chỉ nhận (cổng phải giống với socket bên nhận )
  for(uint32_t i = 0; i < numSensors; i++)
  {
    source[i] = Socket::CreateSocket (sensor.Get(i), tid); // tạo socket ứng với nút gửi
    source[i]->Connect (remote); // thiết lập địa chỉ nhận cho socket
  }

  // Give OLSR time to converge-- 30 seconds, perhaps
  for(int i = 0; i < numSensors; i++)
  {
    Simulator::Schedule (Seconds (30.0 + i*0.3), &GenerateTraffic,
                       source[i], packetSize, numPackets, interPacketInterval);
  }

  Simulator::Stop (Seconds (40.0)); // dừng mô phỏng
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}

