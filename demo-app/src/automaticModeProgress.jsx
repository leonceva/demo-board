import React from 'react'
import { useEffect } from 'react'
import { useState } from 'react'
import ProgressBar from 'react-bootstrap/ProgressBar'


const AutomaticModeProgress = (props) => {

    const [value, setValue] = useState(0)
    const [isRunning, setIsRunning] = useState(true)

    useEffect(() => {
        if (isRunning){            
            const interval = setInterval(() => {
                setValue(oldValue => {
                    const newValue = oldValue + 0.125
                    if ((newValue === props.timerValue) || (newValue > props.timerValue)){
                        clearInterval(interval)
                        setIsRunning(false)
                    }
                    return newValue
                })
            }, 250)
        }
        else{
            setIsRunning(true)
            setValue(0)
        }
    }, [isRunning])

    return(
        <div className="pt m-2">
            {/*{`${"%.2s", value} sec`}*/}
            <ProgressBar animated="true" min={0} now={value} max={props.timerValue}/>
        </div>
    )
}

export default AutomaticModeProgress