----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 08/21/2023 12:20:04 PM
-- Design Name: 
-- Module Name: top - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity top is
    Port ( 
    btn : in STD_LOGIC_VECTOR (3 downto 0);
    led : out STD_LOGIC_VECTOR (3 downto 0)
    );
end top;

architecture Behavioral of top is

component design_1_wrapper is
    port(
        btns : in STD_LOGIC_VECTOR ( 3 downto 0 );
        leds : out STD_LOGIC_VECTOR ( 3 downto 0 )
    );
end component;

begin

ZYNQ : component design_1_wrapper
    port map(
    btns(3 downto 0) => btn(3 downto 0),
    leds(3 downto 0) => led(3 downto 0)
    );

end Behavioral;
