#include <ns3/core-module.h>
#include <ns3/mobility-module.h>
using namespace ns3;
void PrintPosition(Ptr<Node> n)
{
	Vector pos = n->GetObject<MobilityModel>()->GetPosition();
	std::cout<<Simulator::Now().GetSeconds()<<" s, position: "<<pos<<std::endl;
	Simulator::Schedule(Seconds(1), &PrintPosition, n);
}
int main()
{
	Ptr<Node> node = CreateObject<Node>();
	MobilityHelper mobility;
	mobility.SetMobilityModel("ns3::WaypointMobilityModel");
	mobility.Install(node);
	Waypoint wp1(Seconds(0), Vector(0, 0, 0));
	Waypoint wp2(Seconds(10), Vector(20, 40, 0));
	Waypoint wp3(Seconds(15), Vector(60, 80, 0));
	Waypoint wp4(Seconds(25), Vector(80, 120, 0));
	Ptr<WaypointMobilityModel> model = node->GetObject<WaypointMobilityModel>();
	model->AddWaypoint(wp1);
	model->AddWaypoint(wp2);
	model->AddWaypoint(wp3);
	model->AddWaypoint(wp4);
	PrintPosition(node);
	Simulator::Stop(Seconds(25.1));
	Simulator::Run();
	Simulator::Destroy();
	return 0;
}