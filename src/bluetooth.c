

#define BLE_LOG_LEVEL 4
#include <logging/log.h>
LOG_MODULE_REGISTER(ble_log, BLE_LOG_LEVEL);

#include "bluetooth.h"
//#include <settings/settings.h>




//static struct k_work advertise_work;

#define DEVICE_APPEARENCE 0 // unknown appearence
//static uint8_t appearence_data[] = { 0xff, 0xff };
static uint8_t manufacturer_data[] = { 0xff, 0xff };

static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)), 
    //BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
    
    //BT_DATA_BYTES(BT_DATA_UUID16_SOME, BT_UUID_TENNIROBO_VAL),

};

/* Set Scan Response data */
static const struct bt_data sd[] = {
    //BT_DATA_BYTES(BT_DATA_UUID16_SOME, BT_UUID_TENNIROBO_VAL),
    BT_DATA(BT_DATA_MANUFACTURER_DATA, manufacturer_data, 2),
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

static struct bt_conn *current_conn;
static struct bt_conn *auth_conn;

static void advertise(struct k_work *work)
{
	int rc;

	bt_le_adv_stop();

    int err = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
    if (err) {
      LOG_ERR("Advertising failed to start (err %d)", err);
      return;
    }

	LOG_INF("Advertising successfully started");
}

static void connected(struct bt_conn *conn, uint8_t err) {
  char addr[BT_ADDR_LE_STR_LEN];

  if (err) {
    LOG_ERR("Connection failed (err %u)", err);
    return;
  }

  bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));
  LOG_INF("Connected %s", log_strdup(addr));

  current_conn = bt_conn_ref(conn);
}

static void disconnected(struct bt_conn *conn, uint8_t reason) {
  char addr[BT_ADDR_LE_STR_LEN];

  bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

  LOG_INF("Disconnected: %s (reason %u)", log_strdup(addr), reason);
  //k_work_submit(&advertise_work);
  
  if (auth_conn) {
    bt_conn_unref(auth_conn);
    auth_conn = NULL;
  }

  if (current_conn) {
    bt_conn_unref(current_conn);
    current_conn = NULL;
  }
}

static struct bt_conn_cb conn_callbacks = {
    .connected = connected,
    .disconnected = disconnected,
#ifdef CONFIG_BT_NUS_SECURITY_ENABLED
    .security_changed = security_changed,
#endif
};

static void bt_receive_cb(struct bt_conn *conn, const uint8_t *const data, uint16_t len) {
  //int err;
  /*
  char addr[BT_ADDR_LE_STR_LEN] = {0};

  bt_addr_le_to_str(bt_conn_get_dst(conn), addr, ARRAY_SIZE(addr));

  LOG_INF("Received data from: %s", log_strdup(addr));
*/
  LOG_HEXDUMP_DBG(data, len, "BT RX");
  //LOG_("Received BT data ");

}


void error(void) {
  while (true) {
    /* Spin for ever */
    k_sleep(K_MSEC(1000));
  }
}

static void bt_ready(int err)
{
	if (err) {
		LOG_ERR("Bluetooth init failed (err %d)", err);
		return;
	}

	LOG_INF("Bluetooth initialized");

	//k_work_submit(&advertise_work);
    err = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
  if (err) {
    LOG_ERR("Advertising failed to start (err %d)", err);
  }
}


void bluetooth_init(void) {
  int err = 0;
  bt_conn_cb_register(&conn_callbacks);
  //k_work_init(&advertise_work, advertise);
  err = bt_enable(bt_ready);

  if (err) {
    error();
  }
  

  if (IS_ENABLED(CONFIG_SETTINGS)) {
	settings_load();
  }

  #ifdef CONFIG_MCUMGR_SMP_BT
    smp_bt_register();
  #endif
  LOG_INF("Bluetooth initialized");


  //  err = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
  //if (err) {
  //  LOG_ERR("Advertising failed to start (err %d)", err);
  //}
}

bool SendDataToBluetoothComms(uint8_t* p_data, uint16_t p_length)
{
  //uint32_t sendResult = bt_comms_send(NULL,  p_data, p_length);
  //LOG_INF("SendDataToBluetooth result = %d", sendResult);
  //return sendResult == 0 ? true : false;

  return true;
}