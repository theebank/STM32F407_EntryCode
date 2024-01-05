import React, { useEffect, useState } from "react";
import axios from "axios";
import "./App.css";

const App = () => {
  const [data, setData] = useState(null);

  const KeyInput = ({ Digit }) => {
    const buttonPress = async () => {
      try {
        const response = await axios.post("http://localhost:5000/api/input", {
          number: Digit,
        });
        setData(response.data.message);
      } catch (error) {
        console.error(error);
      }
    };

    return <button onClick={buttonPress}>{Digit}</button>;
  };

  return (
    <div>
      <div className="keypad">
        {[1, 2, 3, 4, 5, 6, 7, 8, 9, 0].map((key) => {
          return <KeyInput className="button" Digit={key} />;
        })}
      </div>
    </div>
  );
};

export default App;
