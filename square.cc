// file này để cài đặt một node đi theo quỹ đạo hình vuông
#include "ns3/core-module.h"
#include "ns3/mobility-module.h"
#include "ns3/netanim-module.h"
using namespace ns3;
// các hàm về tọa độ và vận tốc
// để sử dụng các hàm này cần phải Install MobilityModel trước
Vector GetPosition(Ptr<Node> node)
{
  return node -> GetObject<MobilityModel>()->GetPosition();
}
void SetPosition(Ptr<Node> node, double x, double y, double z)
{
  node -> GetObject<MobilityModel>()->SetPosition(Vector(x, y, z));
}
void SetVelocity(Ptr<Node> node , double vx, double vy, double vz)
{
  node -> GetObject<ConstantVelocityMobilityModel>()->SetVelocity(Vector(vx, vy, vz));
}
//Kết thúc các hàm về tọa độ và vận tốc
//Hàm cài đặt một node đi theo quỹ đạo hình vuông 
// các tham số: node: node cần cài đặt
//				initVel: vector vận tốc khởi tạo
//				edge: độ dài cạnh hình vuông

void SquareTrajectory(Ptr<Node> node, Vector initVel, double edge)
{
	std::cout<<"Rotate at "<<Simulator::Now().GetSeconds()<<std::endl;
	double x = initVel.x;
	double y = initVel.y;
	double z = initVel.z;
	SetVelocity(node, x, y, z);
	double velLength = std::sqrt(x*x + y*y + z*z);// độ lớn vector 
	double time = edge/velLength; //thời gian đi hết một cạnh
	//Khi đi đến đỉnh hình vuông ta sẽ xoay vector vận tốc góc 90 độ 
	//Khi xoay vector (x, y) 90 độ theo chiều kim đồng hồ ta được vector(-y, x)
	Simulator::Schedule(Seconds(time), &SquareTrajectory, node, Vector(-y, x, z), edge);
	//schedule là hàm quan trọng trong ns3, chỉ áp dụng cho các hàm có kiểu trả về là void
}
void Stop()
{
	Simulator::Stop();
}
int main()
{
	//tạo node
	NodeContainer n;
	n.Create(1);
	// install mobility model
	MobilityHelper m;
	m.SetMobilityModel("ns3::ConstantVelocityMobilityModel");
	m.Install(n);
	//đặt tọa độ ban đầu
	SetPosition(n.Get(0), 0, 0, 0);
	//đi theo hình vuông
	SquareTrajectory(n.Get(0), Vector(6, 8, 0), 100);
	Simulator::Schedule(Seconds(1000), &Stop);//dừng mô phỏng
	AnimationInterface anim("square.xml");// trực quan hóa quá trình mô phỏng với netanim
	Simulator::Run();
	Simulator::Destroy();
}