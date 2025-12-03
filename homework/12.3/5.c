#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
/*
 * 题目描述：识别ISBN编码
 * 
 * 难度：简单+
 * 
 * 输入：
 * - 一行：一个ISBN号码，格式为"x-xxx-xxxxx-x"
 * - 保证输入符合ISBN的格式要求（包含正确的分隔符和字符数）
 * 
 * 输出：
 * - 如果识别码正确，输出"Right"
 * - 如果识别码错误，输出正确的ISBN号码（格式与原输入相同，只修改识别码）
 * 
 * 规则说明：
 * ISBN格式：x-xxx-xxxxx-x
 * 1. 9位数字 + 1位识别码 + 3位分隔符"-"
 * 2. 识别码计算方法：
 *    - 取前9位数字（忽略分隔符）
 *    - 计算加权和：第1位×1 + 第2位×2 + ... + 第9位×9
 *    - 加权和 mod 11 得到余数
 *    - 如果余数为0-9，识别码为对应数字
 *    - 如果余数为10，识别码为'X'
 * 3. 识别码位置：ISBN号码的最后一位
 * 
 * 示例1：
 * 输入:
 * 0-670-82162-4
 * 输出:
 * Right
 * 
 * 解释:
 * 前9位数字：067082162
 * 加权和：0×1 + 6×2 + 7×3 + 0×4 + 8×5 + 2×6 + 1×7 + 6×8 + 2×9 = 158
 * 158 mod 11 = 4
 * 识别码应为4，与实际识别码4一致，输出"Right"
 * 
 * 示例2：
 * 输入:
 * 0-670-82162-0
 * 输出:
 * 0-670-82162-4
 * 
 * 解释:
 * 前9位数字相同，计算得到识别码应为4
 * 实际识别码为0，错误
 * 输出正确的ISBN：0-670-82162-4
 * 
 * 约束：
 * - 输入字符串长度固定为13（x-xxx-xxxxx-x格式）
 * - 前9个字符为数字或分隔符
 * - 最后一位可能是数字或'X'
 * - 分隔符位置固定：第2、6、12个字符为'-'
 * - 需要保持原格式输出，只修改识别码
 */
void cal(int* input,char sbnum){
    int sum = 0;
    for(int i = 0; i<9; i++){
        sum+=input[i]*(i+1);
    }
    sum%=11;
    if(sum==10 && sbnum=='X'){
        printf("Right\n");
        return;
    }
    if(sum==sbnum - '0'){
        printf("Right\n");
    }else{
        printf("%d",input[0]);
        printf("-");
        printf("%d%d%d",input[1],input[2],input[3]);
        printf("-");
        printf("%d%d%d%d%d",input[4],input[5],input[6],input[7],input[8]);
        printf("-");
        if(sum==10){
            printf("X");
        }else{
            printf("%d",sum);
        }
        
    }

}
int main(){
    char input[14];
    scanf("%s",input);
    int num[9];
    char sbnum = input[12];
    for(int i=0,j=0; i<strlen(input); i++){
        if(isdigit(input[i])){
            num[j++] = input[i]-'0';
        }else{continue;}
    }
    cal(num,sbnum);

}

