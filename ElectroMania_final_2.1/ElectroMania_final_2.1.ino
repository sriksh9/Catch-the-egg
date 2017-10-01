int row[4] = {2, 3, 4, 5};
int col[4] = {6, 7, 8, 9};
byte beep = A2;
int bowl[4] = {10, 11, 12, 13};
byte bowl_pos = 0;
int score = 0, a, b;
int tempo = 0;

void setup()
{
  //Configure the GPIO Pins
  for (int i = 2; i <= 13; i++)
  {
    pinMode(i, OUTPUT);
  }
  pinMode(beep, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);

}

void loop()
{
  int i;
  int decide;
  byte sw_val = 0;             //switch value
  int k = random(1, 1100);
  k = map(k, 1, 1100, 1, 4);
  b = k;
  for (i = 1; i <= 4; i++)
  {
    turn_off_all();
    sw_val = switch_input();
    Serial.println(sw_val);
    glow_bowl(sw_val);
    glow(i, k, 1);              // glowing the matrix with i-rows, k-random_column, high

    tempo = auto_tempo(score);
    Serial.print("Tempo = ");
    Serial.println(tempo);
    delay(tempo);

  }
  a = i;
  decide = result(bowl_pos);
  if (decide == 1)
  {
    score = score + decide;
    digitalWrite(bowl[k - 1], 0);
    delay(100);
    digitalWrite(beep, 1);
    delay(50);
    digitalWrite(beep, 0);

  }
  else
  {
    for (int blnk = 0; blnk < 5; blnk++)
    {
      digitalWrite(bowl[k - 1], 1);
      delay(100);
      digitalWrite(bowl[k - 1], 0);
      delay(100);
    }
    score_indicate();

  }
  Serial.print("Score = ");
  Serial.println(score);
  turn_off_all();

}

void glow(byte r, byte c, boolean val)
{
  digitalWrite(row[r - 1], val);
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(col[i], 1);
    if (i == (c - 1))
      digitalWrite(col[i], 0);
  }
}

void turn_off_all()
{
  for (int j = 1; j <= 4; j++)
  {
    for (int i = 1; i <= 4; i++)
      glow(j, i, 0);
  }
}

byte switch_input()
{
  boolean x, y;
  x = digitalRead(A0);
  if (x == 1)
  {
    Serial.println("LEFT ON");
    delay(20);
    return 1;
  }
  y = digitalRead(A1);
  if (y == 1)
  {
    Serial.println("RIGHT ON");
    delay(20);
    return 2;
  }
  return 0;
}

void glow_bowl(byte val)
{

  if (val == 0)
  {
    clear_bowls();
    Serial.print("POS:");
    Serial.println(bowl_pos);
    digitalWrite(bowl[bowl_pos], 1);

    return;
  }
  if (val == 1)
  {
    clear_bowls();
    if (bowl_pos > 0)
    {
      --bowl_pos;
    }
    constrain(bowl_pos, 1, 4);
    Serial.print("POS:");
    Serial.println(bowl_pos);
    digitalWrite(bowl[bowl_pos], 1);
    return;
  }
  if (val == 2)
  {
    clear_bowls();

    if (bowl_pos < 3)
    {
      ++bowl_pos;
    }
    constrain(bowl_pos, 1, 4);
    Serial.print("POS:");
    Serial.println(bowl_pos);
    digitalWrite(bowl[bowl_pos], 1);
    return;
  }
}

void clear_bowls()
{
  for (int i = 0; i < 4; i++)
    digitalWrite(bowl[i], 0);
}

int result( int pos)
{
  pos++;
  if (a == 5 && pos == b)
  {
    return 1;
  }
  else
  {
    Serial.print("Sorry Dude");
    return 0;
  }
}

void score_indicate()
{
  turn_off_all();
  clear_bowls();
  while (score != 0)
  {
    for (int i = 0; i < 4; i++)
    {
      clear_bowls();
      digitalWrite(bowl[i], 1);
      digitalWrite(beep, 1);
      delay(50);
      digitalWrite(beep, 0);
    }

    for (int i = 0; i < 4; i++)
    {
      clear_bowls();
      digitalWrite(bowl[i], 0);
      delay(50);
    }
    delay(500);
    score--;
  }
  score = 0;
  turn_off_all();
  clear_bowls();
}

int auto_tempo(int value)
{
  int dely;
  dely = map(value, 0, 40, 500, 100);
  return dely;
}

