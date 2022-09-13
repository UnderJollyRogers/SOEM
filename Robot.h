#include "Motor.h"

class Robot
{
    public:
        Robot():maxon1{(uint16) slave1, 1},
                maxon2{(uint16) slave2, 2}
        {
            maxon1.ConfigurePDOs();
            maxon2.ConfigurePDOs();
            Motor::ConfigureMotors();
        }
    private:
        Motor maxon1;
        Motor maxon2;
        uint16_t slave1 = 1;
        uint16_t slave2 = 2;
    public:
        void ConfigureCyclicSynchronousTorqueMode(){
            maxon1.ConfigureCyclicSynchronousPositionMode();
            moxon2.ConfigureCyclicSynchronousPositionMode();
        }
    private:
        void RobotCyclicSynchronousPositionControl(int motorPositions[2], int motorTorques[2]){
            maxon1.SetTargetPosition((int16_t) motorPositions[0]);
            maxon2.SetTargetPosition((int16_t) motorPositions[1]);
            maxon1.SetTargetTorque((int16_t) motorTorques[0]);
            maxon2.SetTargetTorque((int16_t) motorTorques[1]);
            maxon1.SetPositionDemandValue();
            maxon2.SetPositionDemandValue();
            int checker1 = maxon1.GetPositionDemandValue();
            int checker2 = maxon2.GetPositionDemandValue();
            while (checker1!=maxon1.GetTargetPosition() || checker1!=maxon2.GetTargetPosition()){
                this->WritingPDOs();
                Motor::WriteEthercat();
                needlf = TRUE;
                osal_usleep(5000);
                int checker1 = maxon1.GetPositionDemandValue();
                int checker2 = maxon2.GetPositionDemandValue();
            } 
        }
}