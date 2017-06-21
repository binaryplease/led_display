
require 'serialport' # use Kernel::require on windows, works better.
require 'rmagick'
include Magick

port_str = "/dev/ttyACM0"  #may be different for you
baud_rate = 115200
data_bits = 8
stop_bits = 1
parity = SerialPort::NONE

@sp = SerialPort.new(port_str, baud_rate, data_bits, stop_bits, parity)

@width = 15
@height = 9
@wait = 0.01



def set_image

        image = ImageList.new("./image15_9.png")
        image3 = image.quantize(number_colors = 256)

        (0..image.columns).each do |x|
                (0..image.rows).each do |y|
                        pixel = image3.pixel_color(x, y)

                        data = "#{x}:#{y}:#{pixel.red/255}:#{pixel.green/255}:#{pixel.blue/255}"
                        puts data
                        @sp.puts  data
                        sleep @wait

                end
        end
end

def blank_screen
        @width.times do |x|
                @height.times do |y|
                        @sp.puts "#{x}:#{y}:0:0:0"
                        sleep @wait
                end
        end
end





blank_screen
sleep 1
set_image
