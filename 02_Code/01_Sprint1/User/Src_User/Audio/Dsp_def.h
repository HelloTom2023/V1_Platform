

//Commonly Operation Step
#define OPERATION_0    0U
#define OPERATION_1    1U
#define OPERATION_2    2U
#define OPERATION_3    3U
#define OPERATION_4    4U
#define OPERATION_5    5U
#define OPERATION_6    6U
#define OPERATION_7    7U
#define OPERATION_8    8U
#define OPERATION_9    9U
#define OPERATION_10    10U
#define OPERATION_11    11U
#define OPERATION_12    12U
#define OPERATION_13    13U
#define OPERATION_14    14U
#define OPERATION_15    15U
#define OPERATION_16    16U
#define OPERATION_17    17U
#define OPERATION_18    18U
#define OPERATION_19    19U
#define OPERATION_20    20U
#define OPERATION_21    21U

//Commonly Time Def
#define T2MS        2U
#define T4MS        4U
#define T6MS        6U
#define T8MS        8U
#define T10MS    10U
#define T20MS    20U
#define T30MS    30U
#define T35MS    35U
#define T40MS    40U
#define T50MS    50U
#define T60MS    60U
#define T70MS    70U
#define T80MS    80U
#define T100MS    100U
#define T120MS    120U
#define T140MS    140U
#define T150MS    150U
#define T200MS    200U
#define T250MS    250U
#define T300MS    300U
#define T350MS    350U
#define T400MS    400U
#define T500MS    500U
#define T600MS    600U
#define T700MS    700U
#define T800MS    800U
#define T900MS    900U
#define T1S       1000U
#define T1P5S     1500U    // 1.5 Second
#define T2S        2000U
#define T3S        3000U
#define T4S        4000U
#define T5S        5000U
#define T6S        6000U
#define T8S     8000U
#define T10S        10000U    
#define T20S        20000U    
#define T30S        30000U    
#define T1M        60000U    // 1Minute

// Sublayer Execute Enum
typedef enum sublayer_result_enum
{
    SUBLAYER_DOING = 0,    // Sublayer still executing
    SUBLAYER_DONE,        // Sublayer executed
    SUBLAYER_STEP_ERROR,        // Function went to a wrong step
    SUBLAYER_PARAMETER_ERROR,    //Parameter error
    SUBLAYER_TIMEOUT_ERROR,    //Timeout Error
    SUBLAYER_ERROR,        // Sublayer Error
}SUBLAYER_RESULT_ENUM;

//Result Enum
typedef enum result_enum
{
    RESULT_SUCCESS = 0,
    RESULT_SUB_ERR,
    RESULT_PARA_ERR = 0xFE,
}RESULT_ENUM;

//Driver Status
typedef enum driver_state_enum
{
    DRV_STATE_IDLE = 0,
    DRV_STATE_BUSY,
    DRV_STATE_TIMEOUT,
    DRV_STATE_ERROR,
}DRIVER_STATE_ENUM;

#define DRV_UNLOCK         0    //Unlock state
#define DRV_LOCKING     1    //Require Lock
#define DRV_LOCKED         2    //Locked

#define DelayHasExpired(x)    (0 == (x))
#define DelayNotExpired(x)    ((x) > 0)
#define OverTimeExpired(x)    (0 == (x))
#define OverNotExpired(x)        ((x) > 0)

#define MUTE_ON        1
#define MUTE_OFF    0
#define MUTE_NULL    0xFF

//Audio Channel System: Front or Rear
#define SYSTEM_FRONT    0    // Front System Channel
#define SYSTEM_REAR    1    // Rear System Channel: All Rear
#define SYSTEM_ALL        2    // All System Channel
#define SYSTEM_REAR1    3    //independent Rear 1
#define SYSTEM_REAR2    4    //independent Rear 2
#define SYSTEM_INSERT    5
#define SYSTEM_REMOVE    6

#define SYS_MASK_FRONT  0x01
#define SYS_MASK_REAR    0x02
#define SYS_MASK_ALL        0x04

#define STATE_READY    1
#define STATE_INIT        0

#define PI    (3.14159)

#define GPIO_OUTPUT_LOW     0
#define GPIO_OUTPUT_HIGH     1    


#define MODULE_NULL     0x23
#define MODULE_EXIST    0x32
#define MODULE_NONE     0x45

#define Memcpy_U8   API_MemCopy 

