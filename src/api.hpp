#ifndef API_H
#define API_H

// Intervals in ms
#define HEARTBEAT_CHECK_INTERVAL 100L
#define STANDARD_HEARTBEAT_INTERVAL 2000L

#include <map>
#include <string>
#include <vector>
#include "assignment.hpp"
#include "device.hpp"
#include "ros/ros.h"
#include "tapi_msgs/Hello.h"

class Api
{
public:
  // Constructor/Destructor
  explicit Api(ros::NodeHandle* nh);
  ~Api();

  // Public member functions
  void AddDeviceWithoutHello(uint8_t type, std::string name, std::string uuid, unsigned long heartbeat,
                             std::map<std::string, Feature> features);
  bool CheckPending();
  void Clear();
  bool ConnectFeatures(std::string feature1UUID, std::string feature2UUID, double coefficient);
  void DebugOutput();
  bool DeleteConnection(std::string receiverFeatureUUID);
  void Done();
  std::vector<Assignment*> GetConnections();
  std::vector<Device*> GetDevicesSorted();
  void Run();

private:
  // Private member variables
  ros::Publisher configPub;
  std::map<std::string, Assignment> connections;
  std::map<std::string, Device> devices;
  ros::Timer heartbeatCheckTimer;
  ros::ServiceServer helloServ;
  ros::NodeHandle* nh;
  bool pendingChanges;
  ros::AsyncSpinner* spinner;

  // Private member functions
  void changed();
  static bool compareDeviceNames(const Device* first, const Device* second);
  Device* getDeviceByFeatureUUID(std::string uuid);
  void heartbeatCheck(const ros::TimerEvent& e);
  bool hello(tapi_msgs::Hello::Request& helloReq, tapi_msgs::Hello::Response& helloResp);
  void sendAllConnections();
};

#endif  // API_H
