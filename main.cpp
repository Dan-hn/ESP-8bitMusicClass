#include <Arduino.h>
#include <math.h>

#define PIN_READ 4
#define PIN_WRITE 5
#define PIN_W0 5
#define PIN_W1 18
#define elif else if

double mu[12];
double mel[7];
int me[] = {1,1,5,5,6,6,5,0,4,4,3,3,2,2,1};

class MusicP {
    private:
        int _uT = 200;
        double _uHz = 220;
        double _dT0 = 1000/_uHz;
        double _dT = _dT0;
        double _mu[12];
        double _mel[7];
        double _dT_0 = _dT0;
        double _dT_1 = _dT0;
        int _dTt = 0;
    public:
 
        void setup() {
            for(int i = 0; i < 12; i++){
                _mu[i] = pow(1.05946309436,(double)i);
            }
            _mel[0] = 1;
            _mel[1] = _mu[2];
            _mel[2] = _mu[4];
            _mel[3] = _mu[5];
            _mel[4] = _mu[7];
            _mel[5] = _mu[9];
            _mel[6] = _mu[11];
        }
        void playd(int freq) {
            if (freq==0) {
                delay(200);
                return;
            }
            _dT = _dT0/_mel[freq-1];
            for(double i=0;i<_uT;i+=_dT){
                digitalWrite(PIN_WRITE, HIGH);
                delayMicroseconds((_dT/2)*1000);
                digitalWrite(PIN_WRITE, LOW);
                delayMicroseconds((_dT/2)*1000);
            }
            delay(200);
        }
        void play(int freq) {
            if (freq==0) {
                delay(200);
                return;
            }
            _dT = _dT0/_mel[freq-1];
            for(double i=0;i<_uT;i+=_dT){
                digitalWrite(PIN_WRITE, HIGH);
                delayMicroseconds((_dT/2)*1000);
                digitalWrite(PIN_WRITE, LOW);
                delayMicroseconds((_dT/2)*1000);
            }
        }
        // void play(int freq0,int freq1){
        //     if(freq1==0 || freq0==0) {
        //         delay(200);
        //         return;
        //     }elif(freq0==freq1) {
        //         play(freq0);
        //         return;
        //     }elif(freq0 > freq1) {
        //         _dT_0 = _dT0/_mel[freq0-1];
        //         _dT_1 = _dT0/_mel[freq1-1];
        //         _dTt = _dT_1/_dT_0;
        //     } else {
        //         _dT_0 = _dT0/_mel[freq1-1];
        //         _dT_1 = _dT0/_mel[freq0-1];
        //         _dTt = _dT_1/_dT_0;
        //     }//_dT_0 < _dT_1
        //     for(double i=0;i<_uT;i+=_dT_0){
        //         digitalWrite(PIN_W0, HIGH);
        //         digitalWrite(PIN_W1, HIGH);
        //         for(double j=0;j<_dTt;j++){
        //             delayMicroseconds((_dT_0/2)*1000);
        //             digitalWrite(PIN_W0, LOW);
        //             delayMicroseconds((_dT_0/2)*1000);
        //             digitalWrite(PIN_W0, HIGH);
        //         }
        //         delayMicroseconds((_dT_1-_dT_0*_dTt)*1000);
        //         digitalWrite(PIN_W1, LOW);
        //         delayMicroseconds((_dT_0*(_dTt+1)-_dT_1)*1000);
        //         for(double j=0;j<_dTt;j++){
        //             delayMicroseconds((_dT_0/2)*1000);
        //             digitalWrite(PIN_W0, LOW);
        //             delayMicroseconds((_dT_0/2)*1000);
        //             digitalWrite(PIN_W0, HIGH);
        //         }
        //         delayMicroseconds((_dT_1-_dT_0*_dTt)*1000);
        //     }
        // }
        
};
void Music();
void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Serial started");
    pinMode(PIN_READ, INPUT);
    pinMode(PIN_WRITE, OUTPUT);
    pinMode(PIN_W0, OUTPUT);
    pinMode(PIN_W1, OUTPUT);
    for(int i = 0; i < 12; i++){
        mu[i] = pow(1.05946309436,(double)i);
    }
    mel[0] = 1;
    mel[1] = mu[2];
    mel[2] = mu[4];
    mel[3] = mu[5];
    mel[4] = mu[7];
    mel[5] = mu[9];
    mel[6] = mu[11];
    MusicP music;
    music.setup();
    music.play(1);
    music.play(2);
    music.play(3);
    music.play(4);
    music.play(5);
    music.play(4);
    music.play(3);
    music.play(2);
    music.play(1);
    // delay(2000);
    // music.play(1,5);
    // music.play(2,6);
    // music.play(2,6);
    // delay(200);
    // music.play(3);
    // music.play(3,7);
    
}
int count = 0;
void loop() {delay(1000);
    // MusicP music;
    // music.setup();
    // count++;
    // Serial.println("Loop count: " + String(count));
    // delay(1200);
    // Serial.println("PIN 4 ele:"+String(digitalRead(PIN_READ)));
    // delay(100);
    // Serial.print("PIN 5 writing");
    // if (digitalRead(PIN_READ) != HIGH) {
        
    //     delay(0);
    //     for(int i=0;i<100;i+=2){
    //         digitalWrite(PIN_WRITE, HIGH);
    //         delay(1);
    //         digitalWrite(PIN_WRITE, LOW);
    //         delay(1);
    //     }
    // }
    // if (digitalRead(PIN_READ) == HIGH) {
    //     //Music();
    //     // for(int i=0; i<15; i++){
    //     //     music.playd(me[i]);
    //     // }
    //     // music.play(1,5);
    //     // music.play(2,6);
    //     // music.play(3,7);
    //     // music.play(4,1);
    //     // music.play(5,2);
    //     // music.play(6,3);
    //     // music.play(7,4);
    //     delay(500);
    //     music.play(1,5);
    //     music.play(2,6);
    // }
    
    // Serial.println(" done");
}
void Music() {
    int uT = 200;
    double uHz = 220;
    double dT0 = 1000/uHz;
    double dT = dT0;
    
    for(int i=0;i<uT;i+=dT){
        digitalWrite(PIN_WRITE, HIGH);
        delay(dT/2);
        digitalWrite(PIN_WRITE, LOW);
        delay(dT/2);
    }
    delay(200);
    for(int i=0;i<12;i++){
        dT = dT0/mu[i];
        for(int j=0;j<uT;j+=dT){
            digitalWrite(PIN_WRITE, HIGH);
            delayMicroseconds((dT/2)*1000);
            digitalWrite(PIN_WRITE, LOW);
            delayMicroseconds((dT/2)*1000);
        }
    }
    delay(2000);
    for(int i=0;i<7;i++){
        dT = dT0/mel[i];
        for(int j=0;j<uT;j+=dT){
            digitalWrite(PIN_WRITE, HIGH);
            delayMicroseconds((dT/2)*1000);
            digitalWrite(PIN_WRITE, LOW);
            delayMicroseconds((dT/2)*1000);
        }
    }
    for(int i=0;i<15;i++){
        delay(200);
        if (me[i] == 0) {
            delay(200);
            continue;
        }
        dT = dT0/mel[me[i]-1];
        for(int j=0;j<uT;j+=dT){
            digitalWrite(PIN_WRITE, HIGH);
            delayMicroseconds((dT/2)*1000);
            digitalWrite(PIN_WRITE, LOW);
            delayMicroseconds((dT/2)*1000);
        }
    }
    
    
}