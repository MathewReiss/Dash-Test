#include <pebble.h>
#include <pebble-events/pebble-events.h>
#include <pebble-dash-api/pebble-dash-api.h>

#define APP_NAME "Dash Test App"

Window *blank_window;

static void dash_get_data_callback(DataType type, DataValue result){
	switch(type){
		case DataTypeBatteryPercent: APP_LOG(APP_LOG_LEVEL_INFO, "Phone Battery: %d%%", result.integer_value); break;
		case DataTypeWifiNetworkName: APP_LOG(APP_LOG_LEVEL_INFO, "Wifi Network: %s", result.string_value); break;
		case DataTypeStoragePercentUsed: APP_LOG(APP_LOG_LEVEL_INFO, "Storage Free: %d%%", result.integer_value); break;
		case DataTypeStorageFreeGBString: APP_LOG(APP_LOG_LEVEL_INFO, "Storage Free (GB): %s", result.string_value); break;
		case DataTypeGSMOperatorName: APP_LOG(APP_LOG_LEVEL_INFO, "Operator Name: %s", result.string_value); break;
		case DataTypeGSMStrength: APP_LOG(APP_LOG_LEVEL_INFO, "Operator Strength: %d", result.integer_value); break;
	}
}

static void dash_get_feature_callback(FeatureType type, FeatureState state){
	switch(type){
		case FeatureTypeWifi: APP_LOG(APP_LOG_LEVEL_INFO, "Wifi is %s", state == FeatureStateOn ? "ON" : "OFF"); break;
		case FeatureTypeBluetooth: APP_LOG(APP_LOG_LEVEL_INFO, "Bluetooth is %s", state == FeatureStateOn ? "ON" : "OFF"); break;
		case FeatureTypeRinger: APP_LOG(APP_LOG_LEVEL_INFO, "Ringer is %s", state == FeatureStateRingerLoud ? "Loud" : state == FeatureStateRingerVibrate ? "Vibrate" : "Silent"); break;
		case FeatureTypeAutoSync: APP_LOG(APP_LOG_LEVEL_INFO, "Auto Sync is %s", state == FeatureStateOn ? "ON" : "OFF"); break;
		case FeatureTypeHotSpot: APP_LOG(APP_LOG_LEVEL_INFO, "HotSpot is %s", state == FeatureStateOn ? "ON" : "OFF"); break;
		case FeatureTypeAutoBrightness: APP_LOG(APP_LOG_LEVEL_INFO, "Auto Brightness is %s", state == FeatureStateOn? "ON" : "OFF"); break;
	}
}

static void dash_set_feature_callback(FeatureType type, FeatureState state){
	switch(type){
		case FeatureTypeWifi: APP_LOG(APP_LOG_LEVEL_INFO, "Wifi is %s", state == FeatureStateOn ? "ON" : "OFF"); break;
		case FeatureTypeBluetooth: APP_LOG(APP_LOG_LEVEL_INFO, "Bluetooth is %s", state == FeatureStateOn ? "ON" : "OFF"); break;
		case FeatureTypeRinger: APP_LOG(APP_LOG_LEVEL_INFO, "Ringer is %s", state == FeatureStateRingerLoud ? "Loud" : state == FeatureStateRingerVibrate ? "Vibrate" : "Silent"); break;
		case FeatureTypeAutoSync: APP_LOG(APP_LOG_LEVEL_INFO, "Auto Sync is %s", state == FeatureStateOn ? "ON" : "OFF"); break;
		case FeatureTypeHotSpot: APP_LOG(APP_LOG_LEVEL_INFO, "HotSpot is %s", state == FeatureStateOn ? "ON" : "OFF"); break;
		case FeatureTypeAutoBrightness: APP_LOG(APP_LOG_LEVEL_INFO, "Auto Brightness is %s", state == FeatureStateOn? "ON" : "OFF"); break;
	}	
}

static void dash_error_callback(ErrorCode code){
	switch(code){
		case ErrorCodeSuccess: APP_LOG(APP_LOG_LEVEL_INFO, "Success!"); break;
		case ErrorCodeSendingFailed: APP_LOG(APP_LOG_LEVEL_ERROR, "Error: Send Failed"); break;
		case ErrorCodeUnavailable: APP_LOG(APP_LOG_LEVEL_ERROR, "Error: Unavailable"); break;
		case ErrorCodeNoPermissions: APP_LOG(APP_LOG_LEVEL_ERROR, "Error: No Permission"); break;
		case ErrorCodeWrongVersion: APP_LOG(APP_LOG_LEVEL_ERROR, "Error: Wrong Version"); break;
	}
}

void init(){
	blank_window = window_create();
	window_stack_push(blank_window, false);
	
	dash_api_init(APP_NAME, dash_error_callback);
	events_app_message_open();
	
	dash_api_check_is_available();
	
	dash_api_get_data(DataTypeBatteryPercent, dash_get_data_callback);
	dash_api_get_data(DataTypeWifiNetworkName, dash_get_data_callback);
	dash_api_get_data(DataTypeStoragePercentUsed, dash_get_data_callback);
	dash_api_get_data(DataTypeStorageFreeGBString, dash_get_data_callback);
	dash_api_get_data(DataTypeGSMOperatorName, dash_get_data_callback);
	dash_api_get_data(DataTypeGSMStrength, dash_get_data_callback);
	
	dash_api_get_feature(FeatureTypeWifi, dash_get_feature_callback);
	dash_api_get_feature(FeatureTypeBluetooth, dash_get_feature_callback);
	dash_api_get_feature(FeatureTypeRinger, dash_get_feature_callback);
	dash_api_get_feature(FeatureTypeAutoSync, dash_get_feature_callback);
	dash_api_get_feature(FeatureTypeHotSpot, dash_get_feature_callback);
	dash_api_get_feature(FeatureTypeAutoBrightness, dash_get_feature_callback);
}

int main(void){
	init();
	app_event_loop();
}