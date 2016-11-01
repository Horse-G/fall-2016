function out_img = blendImagePair(img1, mask1, img2, mask2, mode)
    % kept getting type errors, so just changed them all to double
    img1 = double(img1);
    img2 = double(img2);
    mask1 = double(mask1);
    mask2 = double(mask2);

    if strcmp(mode, 'blend')
        bw_mask1 = bwdist(~mask1);
        bw_mask2 = bwdist(~mask2);
        w1 = cat(3, bw_mask1, bw_mask1, bw_mask1);
        w2 = cat(3, bw_mask2, bw_mask2, bw_mask2);
        out_img = (img1 .* w1 + img2 .* w2) ./ (w1 + w2);
    elseif strcmp(mode, 'overlay')
        % img1 will only show where mask1 exists and mask2 doesn't
        bw_mask = mask1 & ~mask2;
        w = cat(3,bw_mask,bw_mask,bw_mask);
        out_img = img1 .* w + img2;
    end
end
