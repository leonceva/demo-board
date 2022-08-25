// Header file for XBEE API mode frames
#ifndef FRAMES_H
#define FRAMES_H
// Start Delimeter
#define START "7E"

// Transmit API IDs
#define AT_CMD "08"
#define AT_CMD_Q "09"
#define TRANSMIT "10"
#define EXPL_ADDR "11"
#define REMOTE_AT "17"
#define SRC_ROUTE "21"
#define REG_JOIN_DEVICE "24"

// Received API Types
typedef enum
{
    AT_RESPONSE,
    MDM_STATUS,
    EXT_TX_STATUS,
    RX_PACKET,
    EXPL_RX_IND,
    IO_RX_IND,
    XBEE_SENSOR_READ,
    REMOTE_AT_RESPONSE,
    EXT_MDM_STATUS,
    AIR_FW_UP_STATUS,
    ROUTE_REC_IND,
    MANY_ROUTE_REQ_IND,
    JOIN_STATUS,
    ERROR_API
} receive_type;

// Received API IDs
//#define AT_RESPONSE         "88"
//#define MDM_STATUS          "8A"
//#define EXT_TX_STATUS       "8B"
//#define RX_PACKET           "90"
//#define EXPL_RX_IND         "91"
//#define IO_RX_IND           "92"
//#define XBEE_SENSOR_READ    "94"
//#define REMOTE_AT_RESPONSE  "97"
//#define EXT_MDM_STATUS      "98"
//#define AIR_FW_UP_STATUS    "A0"
//#define ROUTE_REC_IND       "A1"
//#define MANY_ROUTE_REQ_IND  "A3"
//#define JOIN_STATUS         "A5"

// AT Commands
typedef enum
{
    AVAIL_FREQ,
    CHANNEL_MASK,
    MIN_FREQ,
    PREAMBLE_ID,
    NETWORK_ID,
    BROAD_MULTI_TX,
    TX_POWER_LEVEL,
    UNICAST_RETRIES,
    BYTES_TX,
    LAST_PKT_RSSI,
    RX_ERROR_COUNT,
    GOOD_PKT_RX,
    MAC_ACK_FAIL_COUNT,
    TX_FAIL_COUNT,
    UNICAST_ATT_COUNT,
    MAC_UNI_HOP_TIME,
    MAC_BORAD_HOP_TIME,
    ROUTING_MSG_MODE,
    BROADCAST_HOPS,
    NETWORK_HOPS,
    MESH_UNI_RETRIES,
    NETWORK_DELAY_SLOTS,
    SERIAL_NUM_HIGH,
    SERIAL_NUM_LOW,
    DEST_ADDR_HIGH,
    DEST_ADDR_LOW,
    TX_OPTIONS,
    NODE_IDENTIFIER,
    NETWORK_DISC_BKOFF,
    DETWORK_DISC_OPT,
    CLUSTER_ID,
    NETWORK_DISC_TO,
    ENCRYPTION_EN,
    AES_ENCRYPTION_KEY,
    BAUD_RATE,
    PARITY,
    STOP_BITS,
    PACKET_TIMEOUT,
    FLOW_CTRL_THRESHOLD,
    API_ENABLE,
    API_OPTIONS,
    DIO_0_AD_0,
    DIO_1_AD_1_SPI_ATTN,
    DIO_2_AD_2_SPI_SCLK,
    DIO_3_AD_3_SPI_SSEL,
    DIO_4_SPI_MOSI,
    DIO_5_ASSOC_IND,
    DIO_6_RTS,
    DIO_7_CTS,
    DIO_8_SLEEP_REQ,
    DIO_9_ON_SLEEP,
    DIO_10_RSSI_PWM_0,
    DIO_11_PWM_1,
    DIO_12_SPI_MISO,
    DIO_13_DOUT,
    DIO_14_DIN,
    PULL_DIRECTION,
    PULL_UP_DWN_R_EN,
    PWM_0_DUTY_CYCLE,
    PWM_1_DUTY_CYCLE,
    ASSOC_LED_BLINK_T,
    RSSI_PWM_TIMER,
    ANALOG_V_REF,
    DIO_CHANGE_DETECT,
    SLEEP_SAMPLE_RATE,
    SAMPLE_RATE,
    TEMPERATURE,
    SUPPLY_VOLTAGE,
    SLEEP_MODE,
    SLEEP_OPTIONS,
    SLEEP_NUM_CYCLES,
    SLEEP_TIME,
    WAKE_TIME,
    WAKE_HOST_DELAY,
    SLEEP_STATUS,
    OPERATING_SLEEP_T,
    OPERATING_WAKE_T,
    MISS_SYNC_MSGS,
    MISS_SLEEP_SYNC,
    COMMAND_SEQ_CHAR,
    COMMAND_MODE_TO,
    GUARD_TIMES,
    FIRMWARE_VERSION,
    HARDWARE_VERSION,
    HARDWARE_SERIES,
    DEVICE_TYPE_ID,
    MAX_PKT_PAYLOAD,
    CONFIG_CRC,
    QUERIED_SAMPLING,
    ERROR_AT
} AT_type;

// AT Commands - hex value - characters
//  #define AVAIL_FREQ          "4146" // AF
//  #define CHANNEL_MASK        "434D" // CM
//  #define MIN_FREQ            "4D46" // MF
//  #define PREAMBLE_ID         "4850" // HP
//  #define NETWORK_ID          "4944" // ID
//  #define BROAD_MULTI_TX      "4D54" // MT
//  #define TX_POWER_LEVEL      "504C" // PL
//  #define UNICAST_RETRIES     "5252" // RR
//  #define BYTES_TX            "4243" // BC
//  #define LAST_PKT_RSSI       "4442" // DB
//  #define RX_ERROR_COUNT      "4552" // ER
//  #define GOOD_PKT_RX         "4744" // GD
//  #define MAC_ACK_FAIL_COUNT  "4541" // EA
//  #define TX_FAIL_COUNT       "5452" // TR
//  #define UNICAST_ATT_COUNT   "5541" // UA
//  #define MAC_UNI_HOP_TIME    "2548" // %H
//  #define MAC_BORAD_HOP_TIME  "2538" // %8
//  #define ROUTING_MSG_MODE    "4345" // CE
//  #define BROADCAST_HOPS      "4248" // BH
//  #define NETWORK_HOPS        "4E48" // NH
//  #define MESH_UNI_RETRIES    "4D52" // MR
//  #define NETWORK_DELAY_SLOTS "4E4E" // NN
//  #define SERIAL_NUM_HIGH     "5348" // SH
//  #define SERIAL_NUM_LOW      "534C" // SL
//  #define DEST_ADDR_HIGH      "4448" // DH
//  #define DEST_ADDR_LOW       "444C" // DL
//  #define TX_OPTIONS          "544F" // TO
//  #define NODE_IDENTIFIER     "4E49" // NI
//  #define NETWORK_DISC_BKOFF  "4E54" // NT
//  #define DETWORK_DISC_OPT    "4E4F" // NO
//  #define CLUSTER_ID          "4349" // CI
//  #define NETWORK_DISC_TO     "4E3F" // N?
//  #define ENCRYPTION_EN       "4545" // EE
//  #define AES_ENCRYPTION_KEY  "4B59" // KY
//  #define BAUD_RATE           "4244" // BD
//  #define PARITY              "4E42" // NB
//  #define STOP_BITS           "5342" // SB
//  #define PACKET_TIMEOUT      "524F" // RO
//  #define FLOW_CTRL_THRESHOLD "4654" // FT
//  #define API_ENABLE          "4150" // AP
//  #define API_OPTIONS         "414F" // AO
//  #define DIO_0_AD_0          "4430" // D0
//  #define DIO_1_AD_1_SPI_ATTN "4431" // D1
//  #define DIO_2_AD_2_SPI_SCLK "4432" // D2
//  #define DIO_3_AD_3_SPI_SSEL "4433" // D3
//  #define DIO_4_SPI_MOSI      "4434" // D4
//  #define DIO_5_ASSOC_IND     "4435" // D5
//  #define DIO_6_RTS           "4436" // D6
//  #define DIO_7_CTS           "4437" // D7
//  #define DIO_8_SLEEP_REQ     "4438" // D8
//  #define DIO_9_ON_SLEEP      "4439" // D9
//  #define DIO_10_RSSI_PWM_0   "5030" // P0
//  #define DIO_11_PWM_1        "5031" // P1
//  #define DIO_12_SPI_MISO     "5032" // P2
//  #define DIO_13_DOUT         "5033" // P3
//  #define DIO_14_DIN          "5034" // P4
//  #define PULL_DIRECTION      "5044" // PD
//  #define PULL_UP_DWN_R_EN    "5052" // PR
//  #define PWM_0_DUTY_CYCLE    "4D30" // M0
//  #define PWM_1_DUTY_CYCLE    "4D31" // M1
//  #define ASSOC_LED_BLINK_T   "4C54" // LT
//  #define RSSI_PWM_TIMER      "5250" // RP
//  #define ANALOG_V_REF        "4156" // AV
//  #define DIO_CHANGE_DETECT   "4943" // IC
//  #define SLEEP_SAMPLE_RATE   "4946" // IF
//  #define SAMPLE_RATE         "4952" // IR
//  #define TEMPERATURE         "5450" // TP
//  #define SUPPLY_VOLTAGE      "2556" // %V
//  #define SLEEP_MODE          "534D" // SM
//  #define SLEEP_OPTIONS       "534F" // SO
//  #define SLEEP_NUM_CYCLES    "534E" // SN
//  #define SLEEP_TIME          "5350" // SP
//  #define WAKE_TIME           "5354" // ST
//  #define WAKE_HOST_DELAY     "5748" // WH
//  #define SLEEP_STATUS        "5353" // SS
//  #define OPERATING_SLEEP_T   "4F53" // OS
//  #define OPERATING_WAKE_T    "4F57" // OW
//  #define MISS_SYNC_MSGS      "4D53" // MS
//  #define MISS_SLEEP_SYNC     "5351" // SQ
//  #define COMMAND_SEQ_CHAR    "4343" // CC
//  #define COMMAND_MODE_TO     "4354" // CT
//  #define GUARD_TIMES         "4754" // GT
//  #define FIRMWARE_VERSION    "5652" // VR
//  #define HARDWARE_VERSION    "4856" // HV
//  #define HARDWARE_SERIES     "4853" // HS
//  #define DEVICE_TYPE_ID      "4444" // DD
//  #define MAX_PKT_PAYLOAD     "4E50" // NP
//  #define CONFIG_CRC          "434B" // CK
//  #define QUERIED_SAMPLING    "4953" // IS

#endif
