img_list = {'two_objects', 'many_objects_1', 'many_objects_2'};
%threshold_list = [???, ???, ???];

fh1 = figure;
orig_img1 = imread([img_list{1} '.png']);
subplot(2, 2, 1);
imshow(orig_img1); title('Original Image');

bw_img1 = im2bw(orig_img1, .3);
subplot(2, 2, 2);
imshow(bw_img1); title('bw Image');

[labeled_img1,num] = bwlabel(bw_img1);
num
subplot(2,2,3);
imshow(labeled_img1);title('labels?');
% labeled_img should contain labels only from 0-255    
% Cast labeled_img to unit8 so integer labels are preserved
%imwrite(uint8(labeled_img), ['labeled_two_objects.png']);
    
% Assign a unique color to each integer label so the labeled_img can be
% easily examined. 
%rgb_img = label2rgb(labeled_img, 'jet', 'k');
%imwrite(rgb_img, ['rgb_labeled_two_objects.png']);







%function labeled_img = generateLabeledImage(gray_img, threshold)
%    
%end