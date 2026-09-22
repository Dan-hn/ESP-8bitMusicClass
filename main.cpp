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
int me02[]= {5,5,3,4,5,5,3,4,5,15,16,17,1,2,3,4,3,3,1,2,3,3,1,2,3,14,15,16};
int me01[] = {2,1,5,2,1,3,2,1,2,1,6,3,1,3,2,1,2,1,5,2,1,3,2,1,2,1,6,3,1,3,2,1};
int me03[] = {0,1,5,3,0,1,6,3,0,1,5,3,0,1,5,17};
int me00[] = {11,12,13,14,15,16,17,
               1, 2, 3, 4, 5, 6, 7,
              21,22,23,24,25,26,27};
int len00 = sizeof(me00)/sizeof(me00[0]);
int len02 = sizeof(me02)/sizeof(me02[0]);
int len01 = sizeof(me01)/sizeof(me01[0]);
int len03 = sizeof(me03)/sizeof(me03[0]);
class MusicPl {
    private:
        int _uTm = 200000;
        double _uHz = 220;
        double _dT0 = 1000/_uHz;
        double _dTm = _dT0;
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
            int _stepT = 20;
            int _errT = 1;
            bool _isH = false;
            int _uTmp = _uTm;
            if (freq==0) {
                delay(100);
                return;
            }elif(freq>0 && freq<10) {
                _dTm = 500*_dT0/_mel[freq-1];   
            }elif(freq>10 && freq<20) {
                _dTm = 1000*(_dT0/_mel[freq-11]);
                _stepT << 1;
                
            }elif(freq>20 && freq<30) {
                _dTm = 250*_dT0/_mel[freq-21];
            }
            for(double i=0;i<_uTmp;i+=_stepT){
                if ( i < _dTm ){
                    delayMicroseconds(_stepT-_errT);

                }elif(!_isH) {
                    digitalWrite(PIN_WRITE, HIGH);
                    delayMicroseconds(_stepT-_errT);
                    _isH = true;
                    i = 0;
                    _uTmp = _uTmp - _dTm;
                }else {
                    digitalWrite(PIN_WRITE, LOW);
                    delayMicroseconds(_stepT-_errT);
                    _isH = false;
                    i = 0;
                    _uTmp = _uTmp - _dTm;
                }
            }
        }
        void playdf(int freq0,int freq1){
            int _stepT = 10;
            int _errT = 1;
            bool _isH0 = false;
            bool _isH1 = false;
            int _uTmp = _uTm;
            int _dT_u0 = 500*_dT0/_mel[freq0-1];
            int _dT_u1 = 500*_dT0/_mel[freq1-1];
            _dT_0 = _dT_u0;
            _dT_1 = _dT_u1;
            for(int i=0;i<_uTmp;i+=_stepT){
                if(i > _dT_0) {
                    _isH0 = !_isH0;
                    _dT_0 += _dT_u0;
                }
                
                
                if(i > _dT_1 ){
                    _isH1 = !_isH1;
                    _dT_1 += _dT_u1;
                }
                if ( _isH0 || _isH1) {
                    digitalWrite(PIN_WRITE, HIGH);
                
                }else{
                    digitalWrite(PIN_WRITE, LOW);

                }
                delayMicroseconds(_stepT);
                
            }
        }
        
};
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
                delay(100);
                return;
            }elif(freq>0 && freq<10) {
                _dT = _dT0/_mel[freq-1];   
            }elif(freq>10 && freq<20) {
                _dT = 2*(_dT0/_mel[freq-11]);
                
            }elif(freq>20 && freq<30) {
                _dT = 0.5*_dT0/_mel[freq-21];
            }
            for(double i=0;i<_uT;i+=_dT){
                digitalWrite(PIN_WRITE, HIGH);
                delayMicroseconds((_dT/2)*1000);
                digitalWrite(PIN_WRITE, LOW);
                delayMicroseconds((_dT/2)*1000);
            }
            delay(100);
        }
        void play(int freq) {
            if (freq==0) {
                delay(_uT);
                return;
            }elif(freq>0 && freq<10) {
                _dT = _dT0/_mel[freq-1];   
            }elif(freq>10 && freq<20) {
                _dT = 2*(_dT0/_mel[freq-11]);
                
            }elif(freq>20 && freq<30) {
                _dT = 0.5*_dT0/_mel[freq-21];
            }
            for(double i=0;i<_uT;i+=_dT){
                digitalWrite(PIN_WRITE, HIGH);
                delayMicroseconds((_dT/2)*1000);
                digitalWrite(PIN_WRITE, LOW);
                delayMicroseconds((_dT/2)*1000);
            }
        }
        // void playd(int me[]) {
        //     int len = sizeof(me)/sizeof(me[0]);
        //     for(int i=0; i<len; i++){
        //         playd(me[i]);
        //     }
        // }
        void play(int freq0,int freq1){
            if(freq1==0 || freq0==0) {
                delay(200);
                return;
            }elif(freq0==freq1) {
                play(freq0);
                return;
            }elif(freq0 > freq1) {
                _dT_0 = _dT0/_mel[freq0-1];
                _dT_1 = _dT0/_mel[freq1-1];
                _dTt = _dT_1/_dT_0;
            } else {
                _dT_0 = _dT0/_mel[freq1-1];
                _dT_1 = _dT0/_mel[freq0-1];
                _dTt = _dT_1/_dT_0;
            }//_dT_0 < _dT_1
            for(double i=0;i<_uT;i+=_dT_0){
                digitalWrite(PIN_W0, HIGH);
                digitalWrite(PIN_W1, HIGH);
                for(double j=0;j<_dTt;j++){
                    delayMicroseconds((_dT_0/2)*1000);
                    digitalWrite(PIN_W0, LOW);
                    delayMicroseconds((_dT_0/2)*1000);
                    digitalWrite(PIN_W0, HIGH);
                }
                delayMicroseconds((_dT_1-_dT_0*_dTt)*1000);
                digitalWrite(PIN_W1, LOW);
                delayMicroseconds((_dT_0*(_dTt+1)-_dT_1)*1000);
                for(double j=0;j<_dTt;j++){
                    delayMicroseconds((_dT_0/2)*1000);
                    digitalWrite(PIN_W0, LOW);
                    delayMicroseconds((_dT_0/2)*1000);
                    digitalWrite(PIN_W0, HIGH);
                }
                delayMicroseconds((_dT_1-_dT_0*_dTt)*1000);
            }
        }
        
};
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
    MusicPl musicl;
    musicl.setup();
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
    musicl.playd(1);
    musicl.playd(2);
    musicl.playd(3);
    musicl.playd(4);
    musicl.playd(5);

    // delay(2000);
    musicl.playdf(1,5);
    // music.play(2,6);
    // delay(200);
    // music.play(3);
    // music.play(3,7);
    
}

void loop() {
    delay(1000);
    Serial.println("Loop runing...");
    MusicP music;
    MusicPl musicl;
    music.setup();
    musicl.setup();
    if (digitalRead(PIN_READ) == HIGH) {
        //Music();
        /*for(int i=0; i<15; i++){
            music.playd(me[i]);
        }*/
        /*for(int i=0; i<len01; i++){
            music.playd(me01[i]);
        }*/
        for(int i=0; i<len00; i++){
            musicl.playd(me00[i]);
        }
        for(int i=0; i<len03; i++){
            music.playd(me03[i]);
        }
        
        // music.play(1,5);
        // music.play(2,6);
        // music.play(3,7);
        // music.play(4,1);
        // music.play(5,2);
        // music.play(6,3);
        // music.play(7,4);
    }
    if (digitalRead(1) == HIGH) {
        musicl.playdf(1,5);
        musicl.playdf(2,6);

    }
}