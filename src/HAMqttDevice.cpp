#include <HAMqtt.h>

HAMqttDevice::HAMqttDevice(String name, String mac_address){
    _name = name;

    _mac_adress = mac_address;
    _mac_adress.replace(":", "-");

    _identifier = name + _mac_adress.substring(12);
    _identifier.replace(' ', '_');
    _identifier.toLowerCase();
}

/* HAMqttDevice::HAMqttDevice(String name, EspMQTTClient& client) : HAMqttDevice(name){
    setClient(client);
}

void HAMqttDevice::setClient(EspMQTTClient& client){
    _client = &client;
} */

String HAMqttDevice::getAvailabilityTopic(){
    const String ha_topic = HA_TOPIC;
    return ha_topic + getIdentifier() + "/status";
}

String HAMqttDevice::getName(){
    return _name;
}
String HAMqttDevice::getIdentifier(){
    return _identifier;
}

void HAMqttDevice::addConfig(const String &key, const String &value){
    _config.push_back({key, value});
}

String HAMqttDevice::getConfigPayload(){
    String s = "{";

    s += serializerKeyValue("name", _name);
    s += ",";
    s += serializerDict(_config, false);

    std::vector<String> list;
    //list.push_back(_mac_adress); //If more than one device is created they will both have the same ID
    list.push_back(_identifier);
    String identifiers = serializerList(list, true);
    s += ",";

    s += serializerKeyValue("identifiers", identifiers);

    s += "}";

    return s;
}

/* void HAMqttDevice::manageAvailability(uint16_t keepAliveSecond){
    if(!_client->isConnected()){
        return;
    }
    if(millis() - lastAvailabilityMillis > keepAliveSecond*1000){
        sendAvailable();
        lastAvailabilityMillis = millis();
    }
}

void HAMqttDevice::sendAvailable(){
    sendAvailable(true);
}

void HAMqttDevice::sendAvailable(bool available){
    _client->publish(getAvailabilityTopic(), available ? "online" : "offline");
}

EspMQTTClient* HAMqttDevice::getClient(){
    return _client;
} */
