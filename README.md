## 1076042 HW1 2-bit Simple Predictor
此檔案介紹如何使用此程式

## 執行方式
輸入 input 檔案檔名。

## 程式流程
	1. 讀入 Taken/Not Taken 序列
	2. 輸入 Predictor 初始狀態(00)
	3. 進行預測(T/N)
	4. 計算 Misprediction rate
	5. 輸出結果

## FINCTION
bool predictor(string state, string seq);
此 function 用來預測 Taken 或 Not Taken，並回傳下一個狀態(state)。

## INPUT FILE
輸入檔包含 T(Taken) 及 NT(Not Taken)。
* **Example: ** test_case.txt
T NT T T T NT NT NT NT
NT NT T T T T NT T NT
T T T T T NT NT NT NT T NT NT T NT
T T T T T T T T T T
NT NT NT NT NT NT NT

以上總共 5 比測試資料

## OUTPUT FILE
輸出檔包含 Prediction、Miss or not 以及 Misprediction rate。
* **Example: ** test_case_result.txt
Predictor state	00	01	00	01	10	11	10	01	00	
Actual outcome	
Prediction	N	N	N	N	T	T	T	N	N	
Miss		X	V	X	X	V	X	X	V	V	
Misprediction rate: 55.6%

Predictor state	00	00	00	01	10	11	11	10	11	
Actual outcome	
Prediction	N	N	N	N	T	T	T	T	T	
Miss		V	V	X	X	V	V	X	V	X	
Misprediction rate: 44.4%

Predictor state	00	01	10	11	11	11	10	01	00	00	01	00	00	01	
Actual outcome	
Prediction	N	N	T	T	T	T	T	N	N	N	N	N	N	N	
Miss		X	X	V	V	V	X	X	V	V	X	V	V	X	V	
Misprediction rate: 42.9%

Predictor state	00	01	10	11	11	11	11	11	11	11	
Actual outcome	
Prediction	N	N	T	T	T	T	T	T	T	T	
Miss		X	X	V	V	V	V	V	V	V	V	
Misprediction rate: 20.0%

Predictor state	00	00	00	00	00	00	00	
Actual outcome	
Prediction	N	N	N	N	N	N	N	
Miss		V	V	V	V	V	V	V	
Misprediction rate: 0.0%
