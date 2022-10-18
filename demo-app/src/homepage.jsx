import React from "react";
import SensorDashboard from "./sensorDashboard";
import Settings from "./settings";
import logo from "./nait.jpg";
import { useState } from "react";

export const DEFAULT_MIN_TIMER = 10;
export const DEFAULT_MAX_TIMER = 30;

const Homepage = (props) => {
  const [automaticMode, setAutomaticMode] = useState(false);
  const [timerValue, setTimerValue] = useState(DEFAULT_MIN_TIMER)
  const [pingSensors, setPingSensors] = useState(false)
  const [isRunning, setIsRunning] = useState(false)

  return (
    <>
      <div className='p-2 m-2 fs-4'>
        <div className='col m-2'>
          <div className='demo-title row m-2 ps-2 pe-2 fs-1'>
            <div className='col col-1'>
              <img className='logo' src={logo} alt='logo'></img>
            </div>
            <div className='col'>DEMO BOARD</div>
          </div>
          <div className='row m-2'>
            <div className='col m-2'>
              <div className='row m-1'>
                <h3 className='text-center'>SETTINGS</h3>
              </div>
              <div className='row m-1'>
                <Settings
                  automaticMode={automaticMode}
                  setAutomaticMode={setAutomaticMode}
                  timerValue={timerValue}
                  setTimerValue={setTimerValue}
                  pingSensors={pingSensors}
                  setPingSensors={setPingSensors}
                  isRunning={isRunning}
                  setIsRunning={setIsRunning}
                />
              </div>
            </div>
            <div className='col m-2 flx-grow-1'>
              <div className='row m-1'>
                <h3 className='text-center'>SENSORS</h3>
              </div>
              <div className='row m-1'>
                <SensorDashboard automaticMode={automaticMode} pingSensors={pingSensors} setPingSensors={setPingSensors} setIsRunning={setIsRunning} />
              </div>
            </div>
          </div>
        </div>
      </div>
    </>
  );
};

export default Homepage;
