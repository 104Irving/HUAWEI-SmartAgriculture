/*tyh
* * * * * * * * * * * * * * *
* * * * * * * * * * * * * * *
* * * 前端项目主体由@式北完成 * *
* * * * * * * * * * * * * * *
* * * * * * * * * * * * * * *
 */
import axios from '@ohos/axios';

import { LRComponent } from '../view/RegisterAndLoginComponent';

@Entry
@Component
struct Index {
  @State username: string = ''
  @State password: string = ''

  build() {
    Flex({direction:FlexDirection.Column,alignItems:ItemAlign.Center,justifyContent:FlexAlign.SpaceAround}){
      Text('农业灌溉登入端')
        .fontSize(24)
        .fontColor(0xCC6CE7)
        .fontWeight(FontWeight.Bold)
      // Video({
      //   src: "http://192.168.16.4/"
      // }).width("90%").aspectRatio(1.3)
      LRComponent()
    }
    .backgroundImage($r('app.media.maitianbg'))
    .backgroundImageSize(ImageSize.Cover)


  }

  //页面切换
  pageTransition(){
    PageTransitionEnter({ duration: 600 })
      .opacity(0)
    PageTransitionExit({ duration: 600 })
      .opacity(0)
  }
}

