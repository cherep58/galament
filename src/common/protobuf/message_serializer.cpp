#include "message_serializer.h"

#include "common/protobuf/messages.pb.h"

namespace galament::common::protobuf {

static data_types::DataPacket FromProtobuf(const DataPacket& data_packet)
{
	data_types::DataPacket result;
	result.uuid().FromBinaryString(data_packet.uuid());
	result.set_dt(data_types::FromUnixTimestamp(data_packet.dt()));
	result.set_x(data_packet.x());
	result.set_y(data_packet.y());

	return result;
}

static data_types::UuidStatistic FromProtobuf(const UuidStatistic& uuid_statistic)
{
	data_types::UuidStatistic result;
	result.uuid().FromBinaryString(uuid_statistic.uuid());
	result.set_x_1min(uuid_statistic.x_1min());
	result.set_y_1min(uuid_statistic.y_1min());
	result.set_x_5min(uuid_statistic.x_5min());
	result.set_y_5min(uuid_statistic.y_5min());

	return result;
}

static data_types::Statistic FromProtobuf(const Statistic& statistic)
{
	data_types::Statistic result;
	result.reserve(static_cast<size_t>(statistic.uuid_list_size()));

	for (int i = 0; i < statistic.uuid_list_size(); ++i) {
		result.emplace_back(FromProtobuf(statistic.uuid_list(i)));
	}

	return result;
}

static DataPacket* ToProtobuf(const data_types::DataPacket& data_packet)
{
	auto result = new DataPacket();
	auto& uuid = data_packet.uuid().Get();
	result->set_uuid(uuid.begin(), uuid.size());
	result->set_dt(data_types::ToUnixTimestamp(data_packet.dt()));
	result->set_x(data_packet.x());
	result->set_y(data_packet.y());

	return result;
}

static Statistic* ToProtobuf(const data_types::Statistic& statistic)
{
	auto result = new Statistic();

	for (const auto& s : statistic) {
		auto uuid_statistic = result->add_uuid_list();
		auto &uuid = s.uuid().Get();
		uuid_statistic->set_uuid(uuid.begin(), uuid.size());
		uuid_statistic->set_x_1min(s.x_1min());
		uuid_statistic->set_y_1min(s.y_1min());
		uuid_statistic->set_x_5min(s.x_5min());
		uuid_statistic->set_y_5min(s.y_5min());
	}

	return result;
}


std::string MessageSerializer::Serialize(const data_types::DataPacket& data_packet)
{
	Message message;

	message.set_type(Message_Type_DATA_PACKET);
	message.set_allocated_data_packet(ToProtobuf(data_packet));

	return message.SerializeAsString();
}

std::string MessageSerializer::Serialize(const data_types::Statistic& statistic)
{
	Message message;

	message.set_type(Message_Type_STATISTIC_RESPONSE);
	message.set_allocated_statistic(ToProtobuf(statistic));

	return message.SerializeAsString();
}

std::string MessageSerializer::SerializeWithoutPayload(message::MessageType message_type)
{
	Message message;

	message.set_type(static_cast<Message_Type>(message_type));

	return message.SerializeAsString();
}

bool MessageSerializer::Unserialize(std::string_view message, message::MessageVisitor& visitor)
{
	Message protobuf_message;
	if (!protobuf_message.ParseFromArray(message.data(), static_cast<int>(message.size()))) {
		return false;
	}

	if (protobuf_message.type() == Message_Type_DATA_PACKET) {
		if (protobuf_message.has_data_packet()) {
			visitor.Visit(FromProtobuf(protobuf_message.data_packet()));
			return true;
		}
	}
	else if (protobuf_message.type() == Message_Type_STATISTIC_REQUEST) {
		visitor.VisitStatisticRequest();
		return true;
	}
	else if (protobuf_message.type() == Message_Type_STATISTIC_RESPONSE) {
		if (protobuf_message.has_statistic()) {
			visitor.Visit(FromProtobuf(protobuf_message.statistic()));
			return true;
		}
	}

	return false;
}

} // galament::common::protobuf