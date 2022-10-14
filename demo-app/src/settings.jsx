import React from "react";
import AutomaticModeRange from "./automaticModeRange";
import AutomaticModeProgress from "./automaticModeProgress";
import { useState } from "react";
import Button from "react-bootstrap/Button"

const Settings = (props) => {
	
	const [isRunning, setIsRunning] = useState(false)

	return (
		<div className='d-flex flex-row justify-content-evenly settings'>
			<h4 className='pe-3'>Instructions</h4>
			<div className='dashboard p-1'>
				<div className='d-flex flex-row pt-2 pb-3 justify-content-around'>
					<h4
						className={
							`ps-2 pe-2 ` +
							(!props.automaticMode ? `mode-selected` : `mode-unselected`)
						}
					>
						Manual
					</h4>
					<div className='ps-2 pe-2'>
						<div className='form-check form-switch settings-button'>
							<input
								onChange={() => {
									props.setAutomaticMode(!props.automaticMode);
								}}
								className='form-check-input'
								type='checkbox'
								id='flexSwitchCheckDefault'
							/>
						</div>
					</div>
					<h4
						className={
							`ps-2 pe-2 ` +
							(props.automaticMode ? `mode-selected` : `mode-unselected`)
						}
					>
						Automatic
					</h4>
				</div>
				{props.automaticMode && (
					<div className="col flex-column">
						<h5 className='row pt-3 pb-2' style={{ justifyContent: "center" }}>
							{`Automatic Mode Timer: ${props.timerValue}s`}
						</h5>
						<div className="row">
							<AutomaticModeRange disabled={isRunning} timerValue={props.timerValue} setTimerValue={props.setTimerValue} />
						</div>
						<div className="row center" 
							style={{paddingLeft:"25%", paddingRight:"25%", paddingBottom:"2%"}}>
							{isRunning?
								<Button variant="danger" onClick={()=>setIsRunning(!isRunning)}>STOP</Button>
							:	<Button variant="success" onClick={()=>setIsRunning(!isRunning)}>START</Button>

							}
						</div>
						{isRunning &&
						<div className="row" style={{ justifyContent: "center" , paddingBottom:"2%", paddingTop:"2%"}}>
							<AutomaticModeProgress active={isRunning} timerValue={props.timerValue} />
						</div>}
					</div>
				)}
			</div>
		</div>
	);
};

export default Settings;