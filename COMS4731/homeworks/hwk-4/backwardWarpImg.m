function [mask, result_img] = backwardWarpImg(src_img, resultToSrc_H,dest_canvas_width_height)

    width_src = size(src_img,2);
    height_src = size(src_img,1);
    width_result = dest_canvas_width_height(1);
    height_result = dest_canvas_width_height(2);
    
    mask = zeros(height_result, width_result);
    result_img = zeros(height_result, width_result, 3);
    
    for x_result=1:width_result
    for y_result=1:height_result
        pos = resultToSrc_H * [x_result; y_result; 1];
        pos = pos/pos(3);
        if pos(1) <= width_src && pos(1) >= 1 && pos(2) <= height_src && pos(2) >= 1
            mask(y_result,x_result) = 1;
            
            % see nearestNeighbor.m
            result_img(y_result,x_result,:) =...
                src_img(...
                    neighbor(pos(2),1,height_src),...
                    neighbor(pos(1),1,width_src), :);
        end
    end
    end
end
function approx = neighbor(val, min, max)
    if ceil(val) - val > 0.5
        approx = floor(val);
    else
        approx = ceil(val);
    end
    %if val < min
    %    approx = min;
    %elseif val > max
    %    approx = max;
    %end
end