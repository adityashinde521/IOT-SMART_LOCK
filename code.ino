#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

Servo servo_Motor; 
LiquidCrystal lcd(0, 2, 12, 10, 9, 1);
int row[] = {3, A1, 8, A0};
int col[] = {7, 6, 5, 4};
int i,j,lcd_count, count=1, key_id=0, flag, entry=0;
int col_scan;
char temp_press;
char check[6], pass[6];

void setup()
{
servo_Motor.attach(13);
lcd.begin(16,2);
for(i=0;i<=3;i++)
{
pinMode(row[i],OUTPUT);
pinMode(col[i],INPUT);
digitalWrite(col[i],HIGH);
}
lcd.print("SET 5 Digit PASS");
}


void loop()
{
while(entry<=4)
{
SetPassword();
}

key_id=0;
keyscan();

if(key_id==1)
{
check[count]=temp_press;
count++;

if(temp_press == 'A')
{
CheckPassword();
if(flag==0)
{
lcd.setCursor(0,0);
lcd.print("UNLOCKED");
digitalWrite(13,HIGH);
digitalWrite(11,LOW);
servo_Motor.write(90);
}
else{

lcd.setCursor(0,0);
lcd.print("WRONG PASSWORD");
digitalWrite(13,LOW);
digitalWrite(11,HIGH);
delay(200);
lcd.clear();
lcd.print("LOCKED");
servo_Motor.write(13);
}
count=1;
}

else if(temp_press=='C')
{
CheckPassword();
if(flag==0)
{
lcd.setCursor(0,0);
lcd.print("ENTER NEW PASSWORD");
key_id=0;
entry=0;
}else{
lcd.setCursor(0,0);
lcd.print("WRONG PASSWORD");
}
count=1;
}
else if(temp_press=='B')
{
lcd.setCursor(0,0);
lcd.print("LOCKED");
count=1;
}
else if(temp_press=='D')
{
lcd.setCursor(0,0);
lcd.print("PLS ENTER PASS");
count=1;
}

}

}

void SetPassword()
{
keyscan();
if(key_id==1)
{
if(temp_press=='A'|| temp_press=='C' || temp_press=='B')
{
lcd.setCursor(0,0);
lcd.print("INVALID KEYS");
entry=0;
}
else
{
pass[entry]=temp_press;
}
}
key_id=0;
if(entry==5)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("SET LOCKED");
}}

char keyscan()
{
for(i=0; i<=3; i++)
{
digitalWrite(row[0],HIGH);
digitalWrite(row[1],HIGH);
digitalWrite(row[2],HIGH);
digitalWrite(row[3],HIGH);
digitalWrite(row[i],LOW);
for(j=0; j<=3; j++)
{
col_scan=digitalRead(col[j]);
if(col_scan==LOW)
{
key_id ++;
entry++;
temp_press=keypress(i,j);
lcd.setCursor(lcd_count++,1);
lcd.print(temp_press);
if(temp_press=='A' || temp_press=='C' || temp_press=='B')
{
lcd_count=0;
lcd.clear();
}
delay(300);
break;
}}
}}

char keypress(int i, int j)
{
if(i==0 && j==0)
{
return('1');
}
if(i==0 && j==1)
{
return('2');
}
if(i==0 && j==2)
{
return('3');
}
if(i==0 && j==3)
{
return('A');
}
if(i==1 && j==0)
{
return('4');
}
if(i==1 && j==1)
{
return('5');
}
if(i==1 && j==2)
{
return('6');
}
if(i==1 && j==3)
{
return('B');
}
if(i==2 && j==0)
{
return('7');
}
if(i==2 && j==1)
{
return('8');
}
if(i==2 && j==2)
{
return('9');
}
if(i==2 && j==3)
{
return('C');
}
if(i==3 && j==0)
{
return('*');
}
if(i==3 && j==1)
{
return('0');
}
if(i==3 && j==2)
{
return('#');
}
if(i==3 && j==3)
{
return('D');
}
}

void CheckPassword()
{
flag=0;
for(i=1;i<=5&&flag==0;i++)
{
if (check[i]==pass[i])
{
flag=0;
}
else
{
flag=1;
}
}
}
