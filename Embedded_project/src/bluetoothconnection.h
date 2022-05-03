#ifndef _BLECENTERAL_
#define _BLECENTERAL_
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>

extern void start_scan(void);
extern uint8_t notify_func(struct bt_conn *conn,
			   struct bt_gatt_subscribe_params *params,
			   const void *data, uint16_t length);;
static struct bt_conn *default_conn;

static struct bt_uuid_16 uuid = BT_UUID_INIT_16(0);
static struct bt_gatt_discover_params discover_params;
static struct bt_gatt_subscribe_params subscribe_params;

#endif