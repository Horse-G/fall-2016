function result_img = showCorrespondence(orig_img, warped_img, src_pts_nx2, dest_pts_nx2)
    fh = figure;
    imshow([orig_img warped_img]);
    
    for i=1:size(src_pts_nx2,1)
        line([src_pts_nx2(i,1) dest_pts_nx2(i,1)+size(orig_img,2)], [src_pts_nx2(i,2) dest_pts_nx2(i,2)],...
            'LineWidth',2,'Color',[0.5, 0.3, 0.7]);
    end
    
    set(fh, 'WindowStyle', 'normal');
    img = getimage(fh);
    truesize(fh, [size(img, 1), size(img, 2)]);
    frame = getframe(fh);
    frame = getframe(fh);
    pause(0.5); 
    result_img = frame.cdata;
end
