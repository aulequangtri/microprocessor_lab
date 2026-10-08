/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// Mảng lưu trữ 12 chân GPIO từ PA4 đến PA15
uint16_t clock_pins[12] = {
    GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7,
    GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11,
    GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15
};
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();

  /* USER CODE BEGIN 2 */
  int current_led = 0;

  // Đảm bảo tất cả các đèn đều tắt lúc khởi động
  for (int i = 0; i < 12; i++) {
      HAL_GPIO_WritePin(GPIOA, clock_pins[i], GPIO_PIN_RESET);
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      // Bật sáng đèn ở vị trí hiện tại
      HAL_GPIO_WritePin(GPIOA, clock_pins[current_led], GPIO_PIN_SET);

      // Tăng biến đếm để chuyển sang đèn tiếp theo
      current_led++;

      // Khi đã bật sáng đủ 12 đèn
      if (current_led >= 12) {
          HAL_Delay(1000); // Giữ trạng thái sáng toàn bộ trong 1 giây

          // Tắt toàn bộ đèn để bắt đầu chu kỳ mới
          for (int i = 0; i < 12; i++) {
              HAL_GPIO_WritePin(GPIOA, clock_pins[i], GPIO_PIN_RESET);
          }
          current_led = 0; // Reset biến đếm
      }

      // Thời gian trễ giữa mỗi lần bật đèn (500ms)
      HAL_Delay(500);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/* Các hàm SystemClock_Config và MX_GPIO_Init được sinh tự động bởi CubeMX nằm ở dưới này... */
