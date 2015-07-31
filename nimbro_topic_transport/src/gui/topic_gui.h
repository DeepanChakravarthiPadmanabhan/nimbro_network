// Diagnostic GUI for nimbro_topic_transport
// Author: Max Schwarz <max.schwarz@uni-bonn.de>

#ifndef TOPIC_GUI_H
#define TOPIC_GUI_H

#include <ros/subscriber.h>

#include <nimbro_topic_transport/SenderStats.h>
#include <nimbro_topic_transport/ReceiverStats.h>

#include <rqt_gui_cpp/plugin.h>

#include <string>
#include <map>

#include <QTimer>

#include "dot_widget.h"

namespace nimbro_topic_transport
{

struct ConnectionIdentifier
{
	std::string src;
	std::string dest;
	int sourcePort;
	int destPort;

	bool operator==(const ConnectionIdentifier& other) const
	{
		return src == other.src && dest == other.dest
			&& sourcePort == other.sourcePort && destPort == other.destPort;
	}

	bool operator<(const ConnectionIdentifier& other) const
	{
		if(src < other.src)
			return true;
		if(src > other.src)
			return false;

		if(dest < other.dest)
			return true;
		if(dest > other.dest)
			return false;

		if(sourcePort < other.sourcePort)
			return true;
		if(sourcePort > other.sourcePort)
			return false;

		return destPort < other.destPort;
	}
};

class TopicGUI : public rqt_gui_cpp::Plugin
{
Q_OBJECT
public:
	TopicGUI();
	virtual ~TopicGUI();

	virtual void initPlugin(qt_gui_cpp::PluginContext & ) override;
	virtual void shutdownPlugin() override;
Q_SIGNALS:
	void senderStatsReceived(const nimbro_topic_transport::SenderStatsConstPtr& msg);
	void receiverStatsReceived(const nimbro_topic_transport::ReceiverStatsConstPtr& msg);
private Q_SLOTS:
	void handleSenderStats(const nimbro_topic_transport::SenderStatsConstPtr& msg);
	void handleReceiverStats(const nimbro_topic_transport::ReceiverStatsConstPtr& msg);
	void update();
private:
	ros::Subscriber m_sub_senderStats;
	ros::Subscriber m_sub_receiverStats;

	std::map<ConnectionIdentifier, SenderStatsConstPtr> m_senderStats;
	std::map<ConnectionIdentifier, ReceiverStatsConstPtr> m_receiverStats;

	DotWidget* m_w;
};

}

#endif
