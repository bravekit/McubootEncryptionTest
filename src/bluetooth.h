#ifndef __ROBOT_BLUETOOTH_
#define __ROBOT_BLUETOOTH_

#include <zephyr/types.h>
#include <zephyr.h>
#include <drivers/uart.h>

#include <device.h>
#include <soc.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>
#include <mgmt/mcumgr/smp_bt.h>

//#include "utils.h"

//#define BT_UUID_TENNIROBO_VAL BT_UUID_128_ENCODE(0x4B1F65F5, 0xBA7F, 0x461D, 0x8ACC, 0xCF0A90336294)

#define DEVICE_NAME                         "bootTst2"                            /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

//#define HM11_UUID_VAL                      0xFFE0     
//#define BT_UUID_TENNIROBO_VAL                BT_UUID_16_ENCODE(HM11_UUID_VAL)                       // 16 bit UUID - for emulating HM-11





#define APP_BLE_OBSERVER_PRIO               3                                       /**< Application's BLE observer priority. You shouldn't need to modify this value. */
#define APP_BLE_CONN_CFG_TAG                1                                       /**< A tag identifying the SoftDevice BLE configuration. */

#define APP_ADV_INTERVAL                    300                                     /**< The advertising interval (in units of 0.625 ms. This value corresponds to 187.5 ms). */
//#define APP_ADV_DURATION                    18000                                       /**< The advertising duration (180 seconds) in units of 10 milliseconds. */
#define APP_ADV_DURATION                    BLE_GAP_ADV_TIMEOUT_GENERAL_UNLIMITED     // Advertising until app stopps it



#define MIN_CONN_INTERVAL                   MSEC_TO_UNITS(17, UNIT_1_25_MS)        /**< Minimum acceptable connection interval (400 = 0.4 seconds). */
#define MAX_CONN_INTERVAL                   MSEC_TO_UNITS(38, UNIT_1_25_MS)        /**< Maximum acceptable connection interval (600 = 0.65 second). */
#define SLAVE_LATENCY                       0                                       /**< Slave latency. */
#define CONN_SUP_TIMEOUT                    MSEC_TO_UNITS(4000, UNIT_10_MS)         /**< Connection supervisory time-out (4 seconds). */

#define FIRST_CONN_PARAMS_UPDATE_DELAY      5000                                    /**< Time from initiating event (connect or start of notification) to first time sd_ble_gap_conn_param_update is called (5 seconds). */
#define NEXT_CONN_PARAMS_UPDATE_DELAY       30000                                   /**< Time between each call to sd_ble_gap_conn_param_update after the first call (30 seconds). */
#define MAX_CONN_PARAMS_UPDATE_COUNT        3                                       /**< Number of attempts before giving up the connection parameter negotiation. */

#define SEC_PARAM_BOND                      1                                       /**< Perform bonding. */
#define SEC_PARAM_MITM                      0                                       /**< Man In The Middle protection not required. */
#define SEC_PARAM_LESC                      0                                       /**< LE Secure Connections not enabled. */
#define SEC_PARAM_KEYPRESS                  0                                       /**< Keypress notifications not enabled. */
#define SEC_PARAM_IO_CAPABILITIES           BLE_GAP_IO_CAPS_NONE                    /**< No I/O capabilities. */
#define SEC_PARAM_OOB                       0                                       /**< Out Of Band data not available. */
#define SEC_PARAM_MIN_KEY_SIZE              7                                       /**< Minimum encryption key size. */
#define SEC_PARAM_MAX_KEY_SIZE              16                                      /**< Maximum encryption key size. */

#define DEAD_BEEF                           0xDEADBEEF                              /**< Value used as error code on stack dump, can be used to identify stack location on stack unwind. */

#define OSTIMER_WAIT_FOR_QUEUE              2                                       /**< Number of ticks to wait for the timer queue to be ready */






void bluetooth_init(void);
#endif
